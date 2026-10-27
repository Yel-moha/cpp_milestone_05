# Guida semplice — C++ Module 05, ex03

## Obiettivo

Aggiungere la classe `Intern`, che crea uno dei tre moduli già implementati in `ex02`:

- `ShrubberyCreationForm`
- `RobotomyRequestForm`
- `PresidentialPardonForm`

L’intern non ha nome, grado o altri attributi. Il suo compito è solo creare il modulo richiesto.

## Requisiti del subject

`Intern::makeForm()` riceve due stringhe:

1. il nome del tipo di modulo da creare;
2. il target da assegnare al modulo.

Restituisce un puntatore a `AForm`:

```cpp
AForm* makeForm(const std::string& formName,
                const std::string& target) const;