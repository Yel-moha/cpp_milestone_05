#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <exception>
#include <iostream>
#include <cstdlib>

int main()
{
    try
    {
        srand(time(NULL));
        Bureaucrat boss("Boss", 1);
        Bureaucrat trainee("Trainee", 150);

        ShrubberyCreationForm shrubbery("home");
        RobotomyRequestForm robotomy("Marvin");
        PresidentialPardonForm pardon("Ford Prefect");

        std::cout << "=== Forms ===" << std::endl;
        std::cout << shrubbery << std::endl;
        std::cout << robotomy << std::endl;
        std::cout << pardon << std::endl;

        std::cout << "\n=== Refused signing ===" << std::endl;
        trainee.signForm(shrubbery);

        std::cout << "\n=== Refused execution: unsigned form ===" << std::endl;
        boss.executeForm(pardon);

        std::cout << "\n=== Signing all forms ===" << std::endl;
        boss.signForm(shrubbery);
        boss.signForm(robotomy);
        boss.signForm(pardon);

        std::cout << "\n=== Refused execution: insufficient grade ===" << std::endl;
        trainee.executeForm(shrubbery);

        std::cout << "\n=== Successful execution ===" << std::endl;
        boss.executeForm(shrubbery);
        boss.executeForm(robotomy);
        boss.executeForm(pardon);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}