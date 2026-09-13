#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main()
{
    std::cout << "=== INTERN TESTS ===" << '\n' << '\n';

    // Test 1: Creare forme valide
    std::cout << "Test 1: Creating valid forms" << '\n';
    try {
        Intern intern;
        Bureaucrat boss("Boss", 1);
        
        AForm* form1 = intern.makeForm("shrubbery creation", "home");
        AForm* form2 = intern.makeForm("robotomy request", "Bender");
        AForm* form3 = intern.makeForm("presidential pardon", "Arthur Dent");
        
        std::cout << '\n';
        
        // Test form 1
        if (form1) {
            std::cout << "Form 1: " << form1->getName() << '\n';
            boss.signForm(*form1);
            boss.executeForm(*form1);
            delete form1;
        }
        
        std::cout << '\n';
        
        // Test form 2
        if (form2) {
            std::cout << "Form 2: " << form2->getName() << '\n';
            boss.signForm(*form2);
            boss.executeForm(*form2);
            delete form2;
        }
        
        std::cout << '\n';
        
        // Test form 3
        if (form3) {
            std::cout << "Form 3: " << form3->getName() << '\n';
            boss.signForm(*form3);
            boss.executeForm(*form3);
            delete form3;
        }
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    
    std::cout << "\n\nTest 2: Invalid form name" << '\n';
    try {
        Intern intern;
        AForm* invalidForm = intern.makeForm("invalid form", "target");
        
        if (invalidForm == NULL) {
            std::cout << "Correctly returned NULL for invalid form" << '\n';
        }
    }
    catch (std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    
    std::cout << "\n=== END OF TESTS ===" << '\n';
    
    /*  Test pt Schrubbery
    try {
        ShrubberyCreationForm form("garden");
        Bureaucrat bob("Bob", 1);

        std::cout << '\n';
        std::cout << form << '\n';
        std::cout << bob << '\n';ntern-ul nu păstrează acel pointer - îl returnează apelantului
        
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