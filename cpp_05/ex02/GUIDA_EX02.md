# CPP Module 05 — ex02: classi astratte, polimorfismo e `AForm`

Questa guida spiega **cosa chiede il subject**, **perché lo chiede** e un modo pulito per implementarlo in C++98. L'esercizio parte dal risultato di `ex01`: non stai ricominciando da zero, ma stai rendendo `Form` una base comune per più tipi di modulo.

## 1. Il problema da modellare

Un `Bureaucrat` può firmare ed eseguire dei moduli. Tutti i moduli hanno le stesse informazioni amministrative:

- nome;
- stato `signed` / `not signed`;
- grade minimo per firmare;
- grade minimo per eseguire.

Queste regole non devono essere duplicate tre volte. Però l'effetto dell'esecuzione cambia:

| Classe concreta | Grade per firmare | Grade per eseguire | Effetto |
| --- | ---: | ---: | --- |
| `ShrubberyCreationForm` | 145 | 137 | crea `<target>_shrubbery` e vi scrive alberi ASCII |
| `RobotomyRequestForm` | 72 | 45 | rumore di trapano, successo nel 50% dei casi |
| `PresidentialPardonForm` | 25 | 5 | comunica la grazia di Zaphod Beeblebrox |

La classe `AForm` contiene quindi la parte uguale; ogni classe derivata contiene soltanto la propria azione e il proprio `target`.

## 2. Prima nozione: ereditarietà

Con l'ereditarietà una classe derivata *è anche* un oggetto del tipo della sua base:

```cpp
class AForm { /* parte comune */ };

class ShrubberyCreationForm : public AForm
{
    // parte specifica dello shrubbery
};
```

Un oggetto `ShrubberyCreationForm` ha al suo interno anche la parte `AForm`: possiede quindi `name`, stato di firma e grade della base. Poiché l'ereditarietà è `public`, può essere trattato come `AForm`:

```cpp
ShrubberyCreationForm shrubbery("home");
AForm &form = shrubbery; // riferimento alla sua parte-base
```

Questo è il punto essenziale: `Bureaucrat` deve conoscere il contratto comune `AForm`, non i tre tipi particolari. Così `executeForm(const AForm &form)` funziona per tutti e tre.

## 3. Che cos'è una classe astratta

Una classe astratta descrive un concetto comune, ma è incompleta: non ha senso creare un generico modulo senza sapere quale azione eseguirà.

In C++, una classe diventa astratta se dichiara almeno una **funzione virtuale pura**:

```cpp
virtual void executeAction() const = 0;
```

Il `= 0` non assegna zero: è la sintassi C++ per dire “questa funzione non ha implementazione nella base; ogni classe concreta deve fornirla”. Per questo il seguente codice non deve compilare:

```cpp
AForm generic("qualunque", 42, 42); // errore: AForm è astratta
```

Invece ogni classe concreta implementa la funzione:

```cpp
void ShrubberyCreationForm::executeAction() const
{
    // creare e riempire il file
}
```

Una classe derivata che non implementa tutte le funzioni virtuali pure resta a sua volta astratta e non può essere istanziata.

### `A` in `AForm`

La convenzione del subject è semplice: `AForm` significa **Abstract Form**. La rinomina da `Form` serve a rendere visibile che non è più un tipo di modulo concreto.

## 4. Funzioni virtuali e polimorfismo

Una funzione membro dichiarata `virtual` permette il **polimorfismo dinamico**: se chiami la funzione tramite un riferimento o puntatore alla base, C++ sceglie a runtime la versione del vero oggetto.

```cpp
AForm &form = shrubbery;
form.executeAction(); // viene scelta ShrubberyCreationForm::executeAction()
```

Nel tuo esercizio la chiamata importante è questa:

```text
Bureaucrat::executeForm(AForm const&)
          |
          v
AForm::execute(Bureaucrat const&)  [controlli comuni]
          |
          v
executeAction()                    [azione del tipo reale]
```

`Bureaucrat` riceve un `AForm const&`; non deve fare `if` o `dynamic_cast` per distinguere i form. È il polimorfismo a invocare l'azione corretta.

## 5. Il design più pulito: Template Method

Il subject suggerisce che una soluzione è “più elegante”. Questa è la separazione consigliata:

- `AForm::execute(...)` è **concreta** e fa i due controlli validi per tutti;
- `AForm::executeAction()` è **virtuale pura** e fa il lavoro specifico.

Lo schema è noto come *Template Method*: la base stabilisce l'ordine dei passi e delega alle classi figlie solo il passo variabile.

In `AForm.hpp` puoi esprimere il contratto così:

```cpp
class AForm
{
private:
    const std::string _name;
    bool              _isSigned;
    const int         _signGrade;
    const int         _execGrade;

protected:
    virtual void executeAction() const = 0;

public:
    // costruttori canonici, getter, beSigned...
    virtual ~AForm();
    void execute(Bureaucrat const &executor) const;
};
```

`protected` è una buona scelta per `executeAction`: è visibile alle classi derivate, ma non è un'operazione che il codice cliente dovrebbe chiamare direttamente. Anche `public` è tecnicamente valido, ma esporrebbe un'azione senza i controlli di `execute()`.

L'implementazione centrale sarà concettualmente:

```cpp
void AForm::execute(Bureaucrat const &executor) const
{
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _execGrade)
        throw GradeTooLowException();
    executeAction();
}
```

Il confronto può sembrare al contrario: nel subject il grade `1` è il più alto. Quindi un bureaucrat di grade `50` è insufficiente per un requisito `25`, e la condizione corretta è `50 > 25`.

Non mettere i controlli in `executeAction()`: quella funzione deve poter assumere che il form sia firmato e che l'esecutore sia autorizzato. Questo evita copie dello stesso codice nei tre form.

## 6. Eccezioni richieste

Hai già le eccezioni per i grade fuori dall'intervallo `[1, 150]` e per un grade troppo basso in firma/esecuzione. Aggiungi un'eccezione distinta per il modulo non firmato:

```cpp
class FormNotSignedException : public std::exception
{
public:
    virtual const char *what() const throw();
};
```

`throw()` è la sintassi compatibile con C++98 per dichiarare che `what()` non lancia eccezioni. Quando fallisce un controllo, `throw` interrompe `execute()` e trasferisce il controllo al `catch` di `Bureaucrat::executeForm`.

Sequenza da ricordare:

```text
form.execute(executor)
  ├─ non firmato?          -> throw FormNotSignedException
  ├─ grade insufficiente?  -> throw GradeTooLowException
  └─ altrimenti            -> executeAction()
```

## 7. Perché il distruttore deve essere virtuale

Una base polimorfica deve avere un distruttore virtuale:

```cpp
virtual ~AForm();
```

Così, se un giorno usi `AForm *form = new RobotomyRequestForm("Bender");` e poi `delete form;`, C++ distrugge prima `RobotomyRequestForm` e poi `AForm`. Senza `virtual`, distruggere attraverso il puntatore alla base causa comportamento indefinito.

Anche se il tuo `main` può creare gli oggetti sullo stack e non usare `new`, questa è una regola fondamentale delle gerarchie polimorfiche.

## 8. Struttura delle tre classi concrete

Ogni form ha un unico parametro pubblico di costruzione: il `target`. I nomi e i grade, invece, sono fissi e vengono passati al costruttore di `AForm` nella **lista di inizializzazione**.

Esempio strutturale per il form shrubbery:

```cpp
class ShrubberyCreationForm : public AForm
{
private:
    std::string _target;

protected:
    virtual void executeAction() const;

public:
    ShrubberyCreationForm(std::string const &target);
    ShrubberyCreationForm(ShrubberyCreationForm const &other);
    ShrubberyCreationForm &operator=(ShrubberyCreationForm const &other);
    virtual ~ShrubberyCreationForm();
};

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}
```

Non puoi costruire la parte base nel corpo del costruttore: essa viene costruita **prima** di entrare nel corpo. La lista `: AForm(...)` è perciò necessaria, soprattutto perché `AForm` contiene membri `const`.

I valori da usare sono:

```text
ShrubberyCreationForm("target")  : AForm("ShrubberyCreationForm", 145, 137)
RobotomyRequestForm("target")    : AForm("RobotomyRequestForm", 72, 45)
PresidentialPardonForm("target") : AForm("PresidentialPardonForm", 25, 5)
```

## 9. Azioni concrete

### `ShrubberyCreationForm`

Includi `<fstream>`, apri il file `_target + "_shrubbery"` con `std::ofstream`, scrivi un piccolo disegno ASCII e chiudilo. Controlla sempre l'apertura:

```cpp
std::ofstream output((_target + "_shrubbery").c_str());
if (!output)
    throw FileOpenException(); // oppure un'eccezione esplicita equivalente
output << "   /\\\n";
output << "  /  \\\n";
output << " /____\\\n";
```

`std::string::c_str()` è utile in C++98 quando un'API richiede `const char *`. Il file è creato nella directory da cui esegui il programma (normalmente `cpp_05/ex02` se lanci `./Bureaucrat` lì).

### `RobotomyRequestForm`

Stampa prima un rumore di trapano. Poi scegli casualmente successo o fallimento con probabilità 50%. In C++98 puoi usare `<cstdlib>`:

```cpp
if (std::rand() % 2 == 0)
    std::cout << _target << " has been robotomized successfully" << std::endl;
else
    std::cout << "Robotomy failed for " << _target << std::endl;
```

Per avere sequenze diverse a ogni esecuzione, chiama **una sola volta** `std::srand(std::time(NULL));` in `main` (includendo `<cstdlib>` e `<ctime>`). Non richiamare `srand` dentro `executeAction()`: più esecuzioni nello stesso secondo rischiano di ricevere lo stesso seed.

### `PresidentialPardonForm`

È l'azione più semplice: stampa che `_target` è stato graziato da Zaphod Beeblebrox. Anche qui, il controllo firma/grade non va ripetuto: è già garantito da `AForm::execute()`.

## 10. Collegamento con `Bureaucrat`

In `Bureaucrat.hpp` non includere `AForm.hpp`: basta una **forward declaration** prima della classe:

```cpp
class AForm;
```

Poi sostituisci `Form` con `AForm` e dichiara:

```cpp
void signForm(AForm &form) const;
void executeForm(AForm const &form) const;
```

Nel `.cpp`, invece, includi `AForm.hpp`, perché per chiamare `beSigned`, `getName` ed `execute` serve conoscere la definizione completa della classe.

L'implementazione di `executeForm` segue lo stesso stile di `signForm`:

```cpp
void Bureaucrat::executeForm(AForm const &form) const
{
    try
    {
        form.execute(*this);
        std::cout << _name << " executed " << form.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << _name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

Una forward declaration basta nell'header perché lì compaiono solo riferimenti (`AForm &`), non un oggetto `AForm` completo. Un membro `AForm _form;`, invece, richiederebbe l'include completo.

## 11. Forma canonica e membri `const`

Il subject richiede la forma canonica ortodossa per le classi, quindi per ciascuna dichiara:

1. costruttore di default (se ha senso per il tuo design);
2. costruttore di copia;
3. operatore di assegnazione;
4. distruttore.

In `AForm`, `name`, `sign_grade` ed `exec_grade` sono `const`: l'operatore `=` **non può** cambiarli dopo la costruzione. Normalmente copia quindi solo `_isSigned`:

```cpp
AForm &AForm::operator=(AForm const &other)
{
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}
```

Le classi figlie devono inoltre copiare il loro `_target`; possono chiamare l'assegnazione della base e poi assegnare il target.

## 12. Ordine consigliato di implementazione

1. Rinomina ovunque `Form` in `AForm`: inclusi, forward declaration, parametri di `signForm` e `main`. Non lasciare `#include "Form.hpp"`.
2. Completa `AForm`: distruttore virtuale, `execute`, `executeAction() const = 0`, eccezione per form non firmato.
3. Implementa un form alla volta, iniziando da `PresidentialPardonForm` perché stampa soltanto una riga.
4. Implementa `RobotomyRequestForm` e poi `ShrubberyCreationForm` con `<fstream>`.
5. Aggiungi `Bureaucrat::executeForm`.
6. Inserisci tutti i `.cpp` nel `SRCS` del Makefile.
7. Scrivi un `main` di test e compila con `make`.

Nel Makefile, la lista deve almeno contenere:

```make
SRCS = main.cpp Bureaucrat.cpp AForm.cpp \
       ShrubberyCreationForm.cpp RobotomyRequestForm.cpp \
       PresidentialPardonForm.cpp
```

## 13. Test minimi da fare nel `main`

Questi test mostrano al correttore che hai coperto tutte le richieste:

1. Prova a eseguire un form **non firmato**: deve stampare un errore, senza effetto specifico.
2. Fai firmare un form a un bureaucrat con grade insufficiente: deve fallire.
3. Fai firmare correttamente il form e prova a eseguirlo con grade insufficiente: deve fallire.
4. Esegui correttamente tutti e tre i tipi di form.
5. Controlla che sia comparso `target_shrubbery` e che contenga gli alberi ASCII.
6. Esegui più volte la robotomy per vedere entrambi gli esiti.
7. Facoltativo ma utile: passa ciascun form a una funzione che accetta `AForm const &`, per dimostrare il polimorfismo.

Esempio d'uso:

```cpp
Bureaucrat boss("Boss", 1);
Bureaucrat intern("Intern", 150);
ShrubberyCreationForm garden("home");

intern.executeForm(garden); // non firmato: errore
boss.signForm(garden);      // firma
intern.executeForm(garden); // grade insufficiente: errore
boss.executeForm(garden);   // crea home_shrubbery
```

## 14. Errori frequenti

- Tentare `AForm form(...)`: è corretto che non compili; `AForm` deve essere astratta.
- Rendere `beSigned()` pura virtuale: è sbagliato, perché firmare è una regola condivisa e già implementabile nella base.
- Rendere `execute()` pura virtuale e ripetere i due controlli in tre `.cpp`: può funzionare, ma è la soluzione meno elegante che il subject ti invita a evitare.
- Dimenticare `virtual` nel distruttore di `AForm`.
- Mettere `AForm.hpp` in `Bureaucrat.hpp` invece di usare la forward declaration: non sempre rompe il programma, ma aumenta l'accoppiamento e può creare include circolari.
- Includere `Form.hpp` rimasto da ex01: in ex02 deve essere `AForm.hpp`.
- Confrontare i grade nel verso sbagliato: valore numerico più piccolo = autorità maggiore.
- Scrivere nel file prima di verificare firma e grade: la scrittura deve avvenire solo dopo `AForm::execute()`.
- Dimenticare i tre `.cpp` dei form nel Makefile: gli header da soli non vengono collegati.

## 15. Checklist finale

- [ ] `AForm` non è istanziabile.
- [ ] Gli attributi comuni restano `private` in `AForm`.
- [ ] `AForm` ha un distruttore virtuale.
- [ ] `beSigned()` controlla il grade e cambia lo stato.
- [ ] `execute()` rifiuta form non firmati e grade insufficienti.
- [ ] I tre form ricevono solo il `target` nel costruttore e usano i grade richiesti.
- [ ] Le tre azioni specifiche sono diverse e sono raggiunte tramite polimorfismo.
- [ ] `Bureaucrat::executeForm(AForm const &)` stampa successo o un errore esplicito.
- [ ] Il Makefile compila e collega ogni `.cpp`.
- [ ] `make` passa con `-Wall -Wextra -Werror -std=c++98`.

La frase chiave da portare all'esame è: **`AForm` decide quando un modulo può essere eseguito; ogni classe derivata decide che cosa accade quando può esserlo.**
