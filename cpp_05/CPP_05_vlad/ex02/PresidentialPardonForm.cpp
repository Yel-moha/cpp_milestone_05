#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string target):
    AForm("Presidential Pardon Form", 25, 5), target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other):
    AForm(other), target(other.target)
{}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
    if(this != &other)
    {
        AForm::operator=(other);
        this->target = other.target;
    }
    return *this;
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
    if(!this->getIsSigned())
        throw FormNotSignedException();

    if(executor.getGrade() > this->getGradeToExecute())
        throw GradeTooLowException();

    std::cout << BLUE << target << " has been pardoned by Zaphod Beeblebrox.\n" << RESET;
}

PresidentialPardonForm::~PresidentialPardonForm()
{}