# ScalarConverter ex00 - Comandi Singoli Per Test Limite

## Teoria Rapida Dei Tipi

Questi valori sono i riferimenti teorici standard (implementazioni moderne con int a 32 bit e float/double IEEE-754).

### char

- Intervallo dipende dalla piattaforma (char puo essere signed o unsigned).
- In questo progetto, per la stampa caratteri usi il range ASCII stampabile:
- `32` fino a `126` sono stampabili.
- `0` fino a `31` e `127` sono non stampabili.

### int

- Limite positivo: `2147483647` (INT_MAX).
- Limite negativo: `-2147483648` (INT_MIN).
- Overflow oltre questi limiti: non rappresentabile come int.

### float

- Massimo positivo finito: circa `3.4028235e+38` (FLT_MAX).
- Minimo negativo finito: circa `-3.4028235e+38`.
- Minimo positivo normalizzato: circa `1.17549435e-38` (FLT_MIN).
- Minimo negativo normalizzato: circa `-1.17549435e-38`.
- Precisione effettiva: circa 6-7 cifre decimali.
- Interi rappresentabili esattamente fino a `2^24 = 16777216`.
- `16777217` non e rappresentabile esattamente in float.

### double

- Massimo positivo finito: circa `1.7976931348623157e+308` (DBL_MAX).
- Minimo negativo finito: circa `-1.7976931348623157e+308`.
- Minimo positivo normalizzato: circa `2.2250738585072014e-308` (DBL_MIN).
- Minimo negativo normalizzato: circa `-2.2250738585072014e-308`.
- Precisione effettiva: circa 15-16 cifre decimali.
- Interi rappresentabili esattamente fino a `2^53 = 9007199254740992`.

### special values

- `+inf` e `-inf`: infinito positivo/negativo.
- `nan`: Not a Number.
- Versioni float letterali: `+inff`, `-inff`, `nanf`.

## Nota Su tol

`tol` e una tolleranza numerica usata per trattare come intero un valore floating molto vicino a un intero.

Esempio logico:

- se `|x - trunc(x)| < tol`, il valore viene considerato intero
- utile per stampare `.0` o `.0f` quando il numero e praticamente intero

## Build

```bash
make
```

## Tipo CHAR

```bash
./convert a
./convert "'a'"
./convert " "
./convert 0
./convert 31
./convert 32
./convert 126
./convert 127
```

## Tipo INT (limiti 32 bit)

```bash
./convert 2147483647
./convert 2147483648
./convert -2147483648
./convert -2147483649
./convert 42
./convert -42
./convert +42
./convert 00042
```

## Tipo FLOAT (limiti e precisione)

```bash
./convert 0.0f
./convert -0.0f
./convert 1.0f
./convert -1.0f
./convert 42.0f
./convert 42.5f
./convert 16777216.0f
./convert 16777217.0f
./convert 340282346638528859811704183484516925440.0f
./convert 340282346638528859811704183484516925441.0f
```

## Tipo DOUBLE (limiti e precisione)

```bash
./convert 0.0
./convert -0.0
./convert 1.0
./convert -1.0
./convert 42.0
./convert 42.5
./convert 16777216.0
./convert 16777217.0
./convert 340282346638528859811704183484516925440.0
./convert 340282346638528859811704183484516925441.0
```

## Valori SPECIAL

```bash
./convert nan
./convert nanf
./convert +inf
./convert -inf
./convert +inff
./convert -inff
```

## Comandi Mirati Per Testare tol

```bash
./convert 42.0
./convert 42.00000000000001
./convert 42.0000000000001
./convert 42.5
```
