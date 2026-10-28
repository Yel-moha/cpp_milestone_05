#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>

typedef AForm* (*FormCreator)(const std::string&);

struct FormFactory
{
    const char* name;
    FormCreator create;
};

AForm* Intern::createShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target)
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialPardon(const std::string& target)
{
    return new PresidentialPardonForm(target);
}

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
    (void)other;
}

Intern& Intern::operator=(const Intern& other)
{
    (void)other;
    return *this;
}

Intern::~Intern()
{
}

AForm* Intern::makeForm(const std::string& formName,
                        const std::string& target) const
{
    static const FormFactory forms[] =
    {
        {"shrubbery creation", &createShrubbery},
        {"robotomy request", &createRobotomy},
        {"presidential pardon", &createPresidentialPardon}
    };

    int i = 0;
    while (i < 3)
    {
        if (formName == forms[i].name)
        {
            std::cout << "Intern creates " << formName << std::endl;
            return forms[i].create(target);
        }
        ++i;
    }

    std::cout << "Intern: unknown form name: "
              << formName << std::endl;
    return 0;
}