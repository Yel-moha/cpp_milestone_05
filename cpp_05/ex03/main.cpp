#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

#include <iostream>
#include <cstdlib>

int main()
{
    Intern intern;
    Bureaucrat boss("John", 1);
    Bureaucrat trainee("Trainee", 150);

    std::cout << "=== Creazione delle tre form ===" << std::endl;

    AForm* shrubbery = intern.makeForm("shrubbery creation", "home");
    AForm* robotomy = intern.makeForm("robotomy request", "Bender");
    AForm* pardon = intern.makeForm("presidential pardon", "Alice");

    std::cout << "\n=== Test nome non valido ===" << std::endl;
    AForm* unknown = intern.makeForm("coffee request", "office");

    std::cout << "\n=== Test firma rifiutata ===" << std::endl;
    if (shrubbery != 0)
        trainee.signForm(*shrubbery);

    std::cout << "\n=== Test esecuzione di una form non firmata ===" << std::endl;
    if (pardon != 0)
        boss.executeForm(*pardon);

    std::cout << "\n=== Firma delle form ===" << std::endl;
    if (shrubbery != 0)
        boss.signForm(*shrubbery);
    if (robotomy != 0)
        boss.signForm(*robotomy);
    if (pardon != 0)
        boss.signForm(*pardon);

    std::cout << "\n=== Test esecuzione con grado insufficiente ===" << std::endl;
    if (shrubbery != 0)
        trainee.executeForm(*shrubbery);

    std::cout << "\n=== Esecuzione con grado sufficiente ===" << std::endl;
    if (shrubbery != 0)
        boss.executeForm(*shrubbery);
    if (robotomy != 0)
        boss.executeForm(*robotomy);
    if (pardon != 0)
        boss.executeForm(*pardon);

    delete shrubbery;
    delete robotomy;
    delete pardon;
    delete unknown;

    return 0;
}