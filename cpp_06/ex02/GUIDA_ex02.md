# ex02 - Identify real type (guida passo passo)

## Cosa chiede il subject

- Directory: `ex02/` - File: `Makefile`, `*.cpp`, `*.{h,hpp}`
- **Proibito: `std::typeinfo`**. Non puoi includere `<typeinfo>` e quindi niente `typeid`.
- Una classe **`Base`** con **solo un distruttore virtuale pubblico**.
- Tre classi **vuote** `A`, `B`, `C` che ereditano **pubblicamente** da `Base`.
- Queste 4 classi **non** devono essere in forma canonica ortodossa.
- Tre funzioni (libere, non metodi):
  ```cpp
  Base* generate(void);     // crea a caso un A, B o C e lo ritorna come Base*
  void  identify(Base* p);  // stampa "A", "B" o "C" (tramite puntatore)
  void  identify(Base& p);  // stampa "A", "B" o "C" (tramite riferimento)
                            // -> VIETATO usare un puntatore dentro questa funzione
  ```
- Un `main` di test.

**Cast richiesto in questo esercizio: `dynamic_cast`.**

---

## Teoria in breve

### Upcast e downcast
```
        Base
      /  |  \
     A   B   C
```
- **Upcast** (`A*` -> `Base*`): sempre sicuro, è implicito. `generate()` fa questo.
- **Downcast** (`Base*` -> `A*`): **non** è sempre sicuro, perché un `Base*` potrebbe
  puntare a un `B`. Serve un controllo **a runtime**, ed è quello che fa `dynamic_cast`.

### Perché `Base` deve avere un distruttore **virtuale**
1. `dynamic_cast` funziona **solo su classi polimorfiche**, cioè classi con almeno una
   funzione virtuale. Senza `virtual` non compila.
   Il motivo: la funzione virtuale fa creare al compilatore la *vtable*, e lì dentro
   ci sono le informazioni sul tipo reale (RTTI) che `dynamic_cast` legge.
2. Fai `delete` di un `A` tramite un `Base*`. Se il distruttore non è virtuale, il
   comportamento è indefinito, perché il distruttore di `A` non viene chiamato.

È per questo che il subject chiede **solo** il distruttore virtuale: è il minimo
indispensabile per rendere `Base` polimorfica.

### Come si comporta `dynamic_cast` se fallisce
Il punto chiave dell'esercizio:

| Cast su... | Se il tipo è giusto | Se il tipo è sbagliato |
|---|---|---|
| **puntatore** `dynamic_cast<A*>(p)` | ritorna il puntatore | ritorna **`NULL`** |
| **riferimento** `dynamic_cast<A&>(p)` | ritorna il riferimento | **lancia un'eccezione** `std::bad_cast` |

Un riferimento non può essere "nullo", quindi l'unico modo per segnalare il fallimento
è un'eccezione.

---

## ⚠️ Trappola: `std::bad_cast` sta in `<typeinfo>`, che è proibito

Per `identify(Base&)` devi catturare l'eccezione, ma **non puoi includere `<typeinfo>`**.
Soluzione: catturi **qualsiasi** eccezione con `catch (...)`, oppure con
`catch (std::exception &e)` includendo `<exception>`. `bad_cast` deriva da
`std::exception`, quindi la cattura comunque.

```cpp
try
{
    (void)dynamic_cast<A&>(p);  // se p non è un A -> eccezione
    std::cout << "A" << std::endl;
    return ;
}
catch (...) {}
// ... stessa cosa per B e C
```
Il `(void)` serve a non avere un warning per il valore non usato.

---

## File da creare

```
ex02/
├── Makefile
├── main.cpp
├── Base.hpp / Base.cpp
├── A.hpp / A.cpp      (A.cpp può anche non esserci, vedi sotto)
├── B.hpp / B.cpp
├── C.hpp / C.cpp
└── functions.hpp / functions.cpp   (generate + identify; il nome è a tua scelta)
```
Aggiorna `SRCS` nel Makefile con tutti i `.cpp`.

---

## Passo 1 - `Base.hpp` / `Base.cpp`

```cpp
class Base
{
    public:
        virtual ~Base();
};
```
In `Base.cpp`: `Base::~Base() {}`.
**Non** scriverlo come `virtual ~Base() {}` dentro l'header: il subject dice che
un'implementazione nell'header dà 0.

## Passo 2 - `A.hpp`, `B.hpp`, `C.hpp`

Classi vuote che ereditano pubblicamente:
```cpp
#include "Base.hpp"

class A : public Base
{
};
```
Sono vuote, quindi non c'è niente da implementare e il `.cpp` non serve.
Il distruttore lo genera il compilatore ed è virtuale automaticamente, perché quello di `Base` lo è.

---

## Passo 3 - `generate()`

Serve un numero casuale tra 0 e 2. In C++98:
```cpp
#include <cstdlib>  // std::rand, std::srand
#include <ctime>    // std::time
```
- Chiama **`std::srand(std::time(NULL))` UNA sola volta**, all'inizio del `main`.
  Se la chiami dentro `generate()` e chiami `generate()` più volte nello stesso
  secondo, avrai sempre lo stesso risultato.
- In `generate()`: `int r = std::rand() % 3;` e poi uno `switch`/`if`
  che fa `return new A;` / `new B;` / `new C;`.
- Il valore di ritorno è `Base*`: l'upcast da `A*` a `Base*` è implicito.
- Chi chiama `generate()` deve fare `delete`, altrimenti c'è un leak.

Consiglio: dentro `generate()` stampa anche quale tipo hai creato
(es. `"generate: created A"`), così nel main puoi controllare che `identify` dica lo stesso.

---

## Passo 4 - `identify(Base* p)`

Prova i tre `dynamic_cast` su puntatore uno dopo l'altro:
```
se dynamic_cast<A*>(p) != NULL  -> stampa "A"
altrimenti se ... <B*> ...      -> stampa "B"
altrimenti se ... <C*> ...      -> stampa "C"
altrimenti                       -> "Unknown type" (es. p == NULL)
```

## Passo 5 - `identify(Base& p)`

- **Niente puntatori qui dentro.** Non puoi scrivere `&p` e richiamare la versione
  con il puntatore, perché sarebbe barare.
- Tre blocchi `try { dynamic_cast<X&>(p); stampa "X"; return; } catch (...) {}`,
  come nell'esempio sopra.

---

## Passo 6 - `main.cpp`

Cosa testare:
1. `std::srand(std::time(NULL));`
2. Un ciclo (es. 5-10 volte):
   - `Base* p = generate();`
   - `identify(p);`
   - `identify(*p);`  ← la versione con il riferimento (dereferenzi il puntatore)
   - `delete p;`
3. Test diretti, senza caso: `A a; identify(&a); identify(a);` e uguale per B e C.
4. Caso limite: `identify(NULL)`. Fai attenzione all'ambiguità:
   `identify(NULL)` può essere ambiguo tra le due versioni, quindi usa
   `identify(static_cast<Base*>(NULL));`.
   (`identify(*NULL)` **non** farlo: dereferenziare NULL è comportamento indefinito.)
5. Opzionale: una `Base` "pura" (`Base b; identify(&b); identify(b);`) deve dare
   "Unknown".

---

## Checklist prima di consegnare

- [ ] **nessun** `#include <typeinfo>` e nessun `typeid` (`grep -rn typeinfo .`)
- [ ] `Base` ha **solo** il distruttore virtuale pubblico
- [ ] `A`, `B`, `C` ereditano con `public`
- [ ] `identify(Base&)` non usa puntatori
- [ ] `srand` chiamato una sola volta
- [ ] ogni `generate()` ha il suo `delete` (`valgrind ./identify` senza leak)
- [ ] `-Wall -Wextra -Werror -std=c++98` senza warning
- [ ] include guard + niente implementazioni negli header

## Possibili domande in valutazione

- Cosa succede se togli `virtual` dal distruttore di `Base`? (`dynamic_cast` non compila:
  *"source type is not polymorphic"*. Provalo davanti al valutatore.)
- Differenza tra `dynamic_cast` su puntatore e su riferimento? (NULL contro eccezione.)
- Perché non `static_cast`? (Compila, ma **non controlla niente**: se `p` è un `B`, fare
  `static_cast<A*>(p)` ti dà un puntatore "sbagliato" e usarlo è comportamento indefinito.)
- Perché `catch (...)` e non `catch (std::bad_cast&)`? (`bad_cast` è dichiarato in
  `<typeinfo>`, che è proibito.)
- Dove si trova l'informazione sul tipo reale a runtime? (Nella vtable/RTTI,
  che esiste perché `Base` ha una funzione virtuale.)
