# ex01 - Serialization (guida passo passo)

## Cosa chiede il subject

- Directory: `ex01/` - File: `Makefile`, `*.cpp`, `*.{h,hpp}` - Proibito: niente.
- Una classe **`Serializer`** che **non si può istanziare in nessun modo**, con due metodi `static`:
  ```cpp
  static uintptr_t serialize(Data* ptr);    // puntatore -> intero senza segno
  static Data*     deserialize(uintptr_t raw); // intero -> puntatore a Data
  ```
- Una struttura **`Data` non vuota** (deve avere dei membri).
- Un `main` che:
  1. crea un `Data`,
  2. chiama `serialize(&data)`,
  3. passa il risultato a `deserialize()`,
  4. **verifica che il puntatore ottenuto sia uguale all'originale**.

**Cast richiesto in questo esercizio: `reinterpret_cast`.**

---

## Teoria in breve

### Cos'è `uintptr_t`
Un tipo intero senza segno **grande abbastanza da contenere un indirizzo** di memoria.
Su una macchina a 64 bit è grande 8 byte, come un puntatore. Quindi:

```
puntatore  --(reinterpret_cast)-->  uintptr_t  --(reinterpret_cast)-->  puntatore
```

Alla fine si torna **esattamente allo stesso indirizzo**. Lo standard garantisce questo
"giro andata e ritorno" (round-trip).

### Perché `reinterpret_cast` e non `static_cast`
- `static_cast` converte tra tipi **compatibili** (es. `int` -> `double`, `Derived*` -> `Base*`).
  Tra puntatore e intero **non compila**.
- `reinterpret_cast` dice: "prendi questi bit e leggili come un altro tipo". Non fa
  nessun calcolo e nessun controllo, cambia solo **come il compilatore interpreta** il valore.
  È esattamente quello che serve qui.

### Cos'è la "serializzazione"
In generale vuol dire trasformare qualcosa in una forma "piatta" (numeri, byte) per
salvarla o spedirla e poi ricostruirla. Qui la versione è minima: trasformi un
**indirizzo** in un **numero** e lo riporti indietro.
Attenzione: **non** stai copiando i dati di `Data`, stai convertendo solo il suo indirizzo.

---

## ⚠️ Trappola C++98: l'header di `uintptr_t`

```cpp
#include <cstdint>   // NO: è C++11, con -std=c++98 dà errore
#include <stdint.h>  // SI: header C, funziona in C++98
```
(Ho provato: `<cstdint>` con `-std=c++98` dà `#error This file requires ... C++ 2011`.)

---

## File da creare

```
ex01/
├── Makefile
├── main.cpp
├── Data.hpp
├── Serializer.hpp
└── Serializer.cpp
```
Ricordati di aggiornare `SRCS` nel Makefile: `SRCS = Serializer.cpp main.cpp`

---

## Passo 1 - `Data.hpp`

Una `struct` con qualche membro: deve essere **non vuota**.

```cpp
#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data
{
    int         id;
    std::string name;
    // aggiungi quello che vuoi
};

#endif
```
Non serve un `.cpp`: una `struct` senza metodi non ha niente da implementare.

---

## Passo 2 - `Serializer.hpp`

"Non istanziabile in nessun modo" vuol dire che i costruttori **devono essere privati**.
In C++98 non esiste `= delete`, quindi:

- metti costruttore, costruttore di copia, `operator=` e distruttore nella sezione `private:`;
- i metodi `serialize` / `deserialize` vanno in `public:` e sono `static`, così si chiamano senza oggetto: `Serializer::serialize(...)`.

Scheletro:
```cpp
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer &other);
        Serializer &operator=(const Serializer &other);
        ~Serializer();

    public:
        static uintptr_t serialize(Data* ptr);
        static Data*     deserialize(uintptr_t raw);
};

#endif
```

> Domanda tipica in valutazione: *"Perché il costruttore è privato?"*
> Risposta: così nessuno può scrivere `Serializer s;`. La classe è solo un
> "contenitore" di funzioni static.

> L'header deve includere tutto quello che usa (regola del subject): quindi `<stdint.h>`
> e `"Data.hpp"` vanno **dentro** `Serializer.hpp`.

---

## Passo 3 - `Serializer.cpp`

Devi implementare:
- i 4 metodi della forma canonica (anche se privati, è buona norma definirli; `operator=` fa `(void)other; return *this;` come in ex00);
- `serialize`: **un solo** `reinterpret_cast` da `Data*` a `uintptr_t`;
- `deserialize`: **un solo** `reinterpret_cast` da `uintptr_t` a `Data*`.

Ognuna delle due funzioni è una riga. Provaci da solo: lo schema è
`return reinterpret_cast<TIPO_DESTINAZIONE>(valore);`

Nel `.cpp` **non** si ripete la parola `static`, si scrive solo `uintptr_t Serializer::serialize(Data* ptr) { ... }`.

---

## Passo 4 - `main.cpp`

Cosa testare (stampa tutto, così in valutazione si vede):

1. Crea un `Data` e riempi i campi.
2. Stampa l'indirizzo originale: `std::cout << &data`.
3. `uintptr_t raw = Serializer::serialize(&data);` e stampa `raw`
   (in esadecimale si confronta meglio con l'indirizzo: `std::cout << std::hex << raw << std::dec`; `std::hex` sta già in `<iostream>`, non serve `<iomanip>`).
4. `Data* back = Serializer::deserialize(raw);` e stampa `back`.
5. **Confronto:** `if (back == &data)` stampa "OK" altrimenti "KO".
6. Stampa i campi letti attraverso `back` (`back->id`, `back->name`): devono essere quelli originali.

Test extra (facoltativi ma fanno bella figura):
- modifica `back->id` e stampa `data.id`: cambia anche lui, perché è **lo stesso oggetto**;
- prova con un `Data` allocato con `new` (e ricordati il `delete`);
- prova con `NULL`: `serialize(NULL)` deve dare `0`.

---

## Checklist prima di consegnare

- [ ] `make` con `-Wall -Wextra -Werror -std=c++98` senza warning
- [ ] `Data` ha almeno un membro
- [ ] `Serializer s;` **non compila** (provalo e poi togli la riga)
- [ ] uso solo `reinterpret_cast` (niente cast stile C `(uintptr_t)ptr`)
- [ ] `#include <stdint.h>`, non `<cstdint>`
- [ ] include guard in ogni `.hpp`
- [ ] nessuna implementazione di funzioni nei `.hpp`
- [ ] il main stampa chiaramente che `deserialize(serialize(p)) == p`
- [ ] niente leak se usi `new` (`valgrind ./serializer`)

## Possibili domande in valutazione

- Differenza tra `reinterpret_cast` e `static_cast`?
- Perché `uintptr_t` e non `int` o `unsigned int`? (Su 64 bit un `int` è 4 byte, un puntatore 8: perdi metà indirizzo.)
- Stai copiando i dati di `Data`? (No, solo l'indirizzo.)
- Cosa succede se deserializzi un numero inventato? (Ottieni un puntatore a memoria a caso: usarlo è comportamento indefinito.)
