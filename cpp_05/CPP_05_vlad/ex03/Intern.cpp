#include "Intern.hpp"

Intern::Intern()
{}

Intern::Intern(const Intern &other)
{
    (void)other;
}

Intern &Intern::operator=(const Intern &other)
{
    (void)other;
    return *this;
}


AForm *Intern::makeForm(std::string name, std::string target)
{
    
    if(name.compare("shrubbery creation") == 0)
    {
        std::cout << "Intern creates " << name << '\n';
        return new ShrubberyCreationForm(target);
    }
    else if(name.compare("robotomy request") == 0)
    {
        std::cout << "Intern creates " << name << '\n';
        return new RobotomyRequestForm(target);
    }
    else if(name.compare("presidential pardon") == 0)
    {
        std::cout << "Intern creates " << name << '\n';
        return new PresidentialPardonForm(target);
    }
    else
    {
        std::cout << "Unknown type of form!" << '\n';
        return NULL;
    }
}

Intern::~Intern()
{}