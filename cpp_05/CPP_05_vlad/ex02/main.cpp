#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"

int main()
{
    
    /*  Test pt Schrubbery
    try {
        ShrubberyCreationForm form("garden");
        Bureaucrat bob("Bob", 1);

        std::cout << '\n';
        std::cout << form << '\n';
        std::cout << bob << '\n';
        
        bob.signForm(form);
        bob.executeForm(form);
        
        std::cout << GREEN << "\nCheck garden_shrubbery file!" << RESET << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }
    */

    /* Test pt Robotomy
    try {
        RobotomyRequestForm form("house");
        Bureaucrat john("John", 1);

        std::cout << '\n';
        std::cout << form << '\n';
        std::cout << john << '\n';

        john.signForm(form);
        john.executeForm(form);

        std::cout << GREEN << "SUCCES\n" << RESET;; 
    }
    catch (std::exception& e)
    {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }
    */

    /* Test pt Presidential
    try {
        PresidentialPardonForm form("Act 9/11");
        Bureaucrat john("John", 1);

        std::cout << '\n';
        std::cout << form << '\n';
        std::cout << john << '\n';

        john.signForm(form);
        john.executeForm(form);

        std::cout << GREEN << "SUCCES\n" << RESET;; 
    }
    catch (std::exception& e)
    {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }
    */

    return 0;
}