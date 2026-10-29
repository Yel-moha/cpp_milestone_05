# C++ Module 06 - Guida agli esercizi

Questa guida spiega gli esercizi del Capitolo V, VI e VII:

- `ex00`: conversione di tipi scalari;
- `ex01`: serializzazione di un puntatore;
- `ex02`: identificazione del tipo reale di un oggetto.

Il modulo è dedicato soprattutto ai cast del C++:

| Cast | Uso principale |
|---|---|
| `static_cast` | Conversioni esplicite tra tipi compatibili |
| `reinterpret_cast` | Reinterpretazione di un indirizzo o di una rappresentazione |
| `dynamic_cast` | Identificazione runtime di un oggetto polimorfico |

Il codice deve essere compilato in C++98, come normalmente richiesto dal progetto.

---

## Ex00 - Conversion of scalar types

### Obiettivo

Implementare una classe `ScalarConverter` con un solo metodo pubblico:

```cpp
static void convert(const std::string& literal);
```

Il metodo riceve una stringa che rappresenta un literal C++ e deve:

1. riconoscere il tipo del literal;
2. convertirlo nel tipo corretto;
3. convertirlo negli altri tre tipi scalari;
4. stampare i risultati nell'ordine:
   - `char`;
   - `int`;
   - `float`;
   - `double`.

La classe non deve conservare dati e non deve essere istanziabile.

### Input da gestire

#### Char

Esempi:

```text
'a'
'c'
'*'
```

Il carattere è racchiuso tra apici singoli. La stringa ha quindi la forma:

```text
'x'
```

#### Int

Esempi:

```text
0
42
-42
+42
```

Sono ammessi un eventuale segno e una sequenza di cifre.

#### Float

Esempi:

```text
0.0f
42.0f
-4.2f
```

Il suffisso `f` identifica il tipo `float`.

#### Double

Esempi:

```text
0.0
42.0
-4.2
```

Il double è simile al float, ma non termina con `f`.

#### Pseudo-literal

Per `float`:

```text
nanf
+inff
-inff
```

Per `double`:

```text
nan
+inf
-inf
```

`nan` significa “Not a Number”, mentre `inf` rappresenta l'infinito.

### Output atteso

Per:

```bash
./convert 42
```

l'output deve essere simile a:

```text
char: '*'
int: 42
float: 42.0f
double: 42.0
```

Per:

```bash
./convert nan
```

il risultato deve essere:

```text
char: impossible
int: impossible
float: nanf
double: nan
```

Per:

```bash
./convert 42.0f
```

il risultato deve essere:

```text
char: '*'
int: 42
float: 42.0f
double: 42.0
```

### Riconoscimento del tipo

Una strategia ordinata è:

1. controllare prima gli pseudo-literal;
2. controllare se la stringa ha la forma di un char;
3. controllare se termina con `f`, quindi analizzarla come float;
4. controllare se contiene un punto, quindi analizzarla come double;
5. in caso contrario, analizzarla come int.

È comunque necessario validare realmente la stringa. Non basta decidere il tipo guardando soltanto l'ultimo carattere.

Esempio per il char:

```cpp
literal.length() == 3 &&
literal[0] == '\'' &&
literal[2] == '\''
```

Il valore è:

```cpp
char value = literal[1];
```

### Parsing numerico

Nel progetto è autorizzata una funzione che converta stringhe in numeri, ad esempio:

```cpp
std::strtol
std::strtof
std::strtod
```

Header utili:

```cpp
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <cmath>
#include <limits>
```

Quando si usa una funzione di parsing è importante verificare:

- se la stringa contiene caratteri non validi;
- se è stato consumato l'intero input;
- se il valore è fuori dai limiti del tipo;
- se si è verificato un overflow.

### Conversioni

Dopo aver ottenuto il valore, le conversioni esplicite possono essere fatte con `static_cast`:

```cpp
char c = static_cast<char>(value);
int i = static_cast<int>(value);
float f = static_cast<float>(value);
double d = static_cast<double>(value);
```

Prima di convertire è però necessario controllare che la conversione sia sensata.

### Conversione a char

Un valore numerico può essere stampato come char soltanto se:

1. è finito;
2. rientra nell'intervallo rappresentabile da `char`;
3. è un carattere displayable.

Per l'ASCII stampabile si usa normalmente:

```text
32 <= valore <= 126
```

Esempi:

| Input | Output char |
|---:|---|
| `7` | `Non displayable` |
| `32` | carattere spazio |
| `65` | `'A'` |
| `97` | `'a'` |
| `nan` | `impossible` |

Se il valore è rappresentabile ma non visibile, stampare:

```text
char: Non displayable
```

Se non è convertibile, stampare:

```text
char: impossible
```

### Conversione a int

La conversione a `int` è impossibile quando il valore:

- è `nan`;
- è infinito;
- è fuori dall'intervallo di `int`.

I limiti possono essere ottenuti con:

```cpp
std::numeric_limits<int>::min()
std::numeric_limits<int>::max()
```

### Formattazione di float e double

Per un valore intero come `42`, l'output deve mantenere l'indicazione del tipo:

```text
float: 42.0f
double: 42.0
```

Il suffisso `f` va stampato per i float, ma non per i double.

Per i valori speciali:

```text
float: nanf
double: nan
```

### Classe non istanziabile

Una possibile dichiarazione è:

```cpp
class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter&);
    ScalarConverter& operator=(const ScalarConverter&);
    ~ScalarConverter();

public:
    static void convert(const std::string& literal);
};
```

Il costruttore privato impedisce:

```cpp
ScalarConverter converter;
```

Il metodo si usa invece così:

```cpp
ScalarConverter::convert("42");
```

### Casi di test consigliati

```text
0
-42
42.0
42.0f
'a'
'*'
nan
nanf
+inf
-inff
2147483648
999999999999999999999999
```

---

## Ex01 - Serialization

### Obiettivo

Implementare una classe `Serializer` con due metodi statici:

```cpp
static uintptr_t serialize(Data* ptr);
static Data* deserialize(uintptr_t raw);
```

Il primo metodo converte un puntatore `Data*` in un intero `uintptr_t`.
Il secondo riconverte quell'intero in un puntatore `Data*`.

Anche `Serializer` non deve essere istanziabile.

### Che cos'è `uintptr_t`

`uintptr_t` è un tipo intero senza segno abbastanza grande da contenere un indirizzo.

La serializzazione richiesta è quindi:

```text
Data* -> uintptr_t
```

e la deserializzazione:

```text
uintptr_t -> Data*
```

Non viene copiato il contenuto dell'oggetto. Viene rappresentato come numero il suo indirizzo di memoria.

### Struttura Data

Deve essere creata una struttura non vuota, per esempio:

```cpp
struct Data
{
    int number;
    std::string text;
};
```

Una struttura vuota non soddisfa la richiesta.

### `reinterpret_cast`

La conversione può essere implementata così:

```cpp
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}
```

La conversione inversa:

```cpp
Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

Questo cast non modifica l'oggetto. Reinterpreta soltanto il valore dell'indirizzo.

### Test richiesto

Il programma deve:

1. creare un oggetto `Data`;
2. salvare il suo indirizzo;
3. serializzare il puntatore;
4. deserializzare il numero;
5. confrontare il puntatore ottenuto con quello originale.

Esempio:

```cpp
Data data;
data.number = 42;
data.text = "hello";

Data* original = &data;
uintptr_t raw = Serializer::serialize(original);
Data* restored = Serializer::deserialize(raw);

if (original == restored)
    std::cout << "Pointers are equal" << std::endl;
else
    std::cout << "Pointers are different" << std::endl;
```

L'output corretto è:

```text
Pointers are equal
```

### Classe non istanziabile

Struttura possibile:

```cpp
class Serializer
{
private:
    Serializer();
    Serializer(const Serializer&);
    Serializer& operator=(const Serializer&);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

### Errori da evitare

- usare `static_cast` al posto di `reinterpret_cast`;
- creare una `Data` vuota;
- confrontare il contenuto invece degli indirizzi;
- dimenticare `#include <stdint.h>` oppure il tipo richiesto dal progetto;
- usare un puntatore dopo che l'oggetto puntato è stato distrutto.

---

## Ex02 - Identify real type

### Obiettivo

Creare una gerarchia polimorfica:

```text
Base
|- A
|- B
`- C
```

Le classi richieste sono:

```cpp
class Base
{
public:
    virtual ~Base();
};

class A : public Base
{
};

class B : public Base
{
};

class C : public Base
{
};
```

`A`, `B` e `C` possono essere vuote.

### Perché il distruttore è virtuale

Il distruttore virtuale rende `Base` polimorfica. Questo permette di distruggere correttamente un oggetto derivato attraverso un puntatore alla base:

```cpp
Base* ptr = new A;
delete ptr;
```

Senza distruttore virtuale, la distruzione tramite `Base*` non sarebbe corretta.

### Funzione `generate`

Firma:

```cpp
Base* generate(void);
```

Deve creare casualmente un oggetto `A`, `B` oppure `C` e restituirlo come `Base*`.

Esempio:

```cpp
int choice = std::rand() % 3;

if (choice == 0)
    return new A;
if (choice == 1)
    return new B;
return new C;
```

Uso:

```cpp
Base* object = generate();
identify(object);
delete object;
```

La memoria allocata con `new` deve essere liberata con `delete`.

### `identify(Base* p)`

Firma:

```cpp
void identify(Base* p);
```

Questa funzione deve stampare il tipo reale dell'oggetto puntato.

Implementazione concettuale:

```cpp
if (dynamic_cast<A*>(p))
    std::cout << "A" << std::endl;
else if (dynamic_cast<B*>(p))
    std::cout << "B" << std::endl;
else if (dynamic_cast<C*>(p))
    std::cout << "C" << std::endl;
```

Quando il cast verso il tipo sbagliato fallisce, il risultato è `NULL`.

Per esempio, se `p` punta a `B`:

```cpp
dynamic_cast<A*>(p) // NULL
dynamic_cast<B*>(p) // puntatore valido
```

### `identify(Base& p)`

Firma:

```cpp
void identify(Base& p);
```

In questa funzione è vietato usare un puntatore. Non si può quindi scrivere:

```cpp
dynamic_cast<A*>(&p);
```

Bisogna usare il cast verso reference:

```cpp
try
{
    dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
}
catch (std::exception&)
{
}
```

Se il tipo è diverso da `A`, `dynamic_cast<A&>(p)` lancia un'eccezione. Si può quindi provare con `B` e poi con `C`.

Schema:

```cpp
try
{
    dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
}
catch (std::exception&)
{
    try
    {
        dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
    }
    catch (std::exception&)
    {
        try
        {
            dynamic_cast<C&>(p);
            std::cout << "C" << std::endl;
        }
        catch (std::exception&)
        {
        }
    }
}
```

### Differenza tra cast a puntatore e a reference

| Cast | Se fallisce |
|---|---|
| `dynamic_cast<A*>(p)` | restituisce `NULL` |
| `dynamic_cast<A&>(p)` | lancia un'eccezione |

### Divieto di `typeinfo`

Non bisogna includere:

```cpp
#include <typeinfo>
```

e non bisogna usare:

```cpp
typeid(...)
```

L'identificazione deve essere fatta con `dynamic_cast`.

### Test consigliato

```cpp
Base* object = generate();

identify(object);
identify(*object);

delete object;
```

Le due chiamate devono stampare lo stesso tipo, ad esempio:

```text
B
B
```

È inoltre utile testare direttamente:

```cpp
A a;
B b;
C c;

identify(&a);
identify(a);
identify(&b);
identify(b);
identify(&c);
identify(c);
```

---

## Checklist finale

### Ex00

- [ ] `ScalarConverter::convert` è statico.
- [ ] La classe non è istanziabile.
- [ ] Sono gestiti `char`, `int`, `float` e `double`.
- [ ] Sono gestiti `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`.
- [ ] Sono controllati overflow e conversioni impossibili.
- [ ] I char non displayable stampano `Non displayable`.
- [ ] I float terminano con `f`.
- [ ] Il programma funziona con un solo argomento.

### Ex01

- [ ] `Data` contiene almeno un membro.
- [ ] `serialize` restituisce `uintptr_t`.
- [ ] `deserialize` restituisce `Data*`.
- [ ] È usato `reinterpret_cast`.
- [ ] Il puntatore deserializzato è uguale all'originale.
- [ ] `Serializer` non è istanziabile.

### Ex02

- [ ] `Base` ha un distruttore virtuale.
- [ ] `A`, `B` e `C` ereditano pubblicamente da `Base`.
- [ ] `generate` crea casualmente uno dei tre tipi.
- [ ] `identify(Base*)` usa `dynamic_cast` a puntatore.
- [ ] `identify(Base&)` usa `dynamic_cast` a reference.
- [ ] In `identify(Base&)` non vengono usati puntatori.
- [ ] Non viene incluso `<typeinfo>`.
- [ ] Gli oggetti creati con `new` vengono eliminati con `delete`.

## Differenza riassuntiva

| Esercizio | Input | Operazione |
|---|---|---|
| `ex00` | Stringa come `"42.0f"` | Parsing e conversione tra scalari |
| `ex01` | `Data*` | Puntatore <-> `uintptr_t` |
| `ex02` | `Base*` o `Base&` | Identificazione del tipo derivato |

