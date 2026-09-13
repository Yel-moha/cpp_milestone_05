#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string target) :
    AForm("Robotomy Request Form", 72, 45), target(target)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) :
    AForm(other), target(other.target)
{}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
    if(this != &other)
    {
        AForm::operator=(other);
        this->target = other.target;
    }

    return *this;
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
    if(!this->getIsSigned())
        throw FormNotSignedException();

    if(executor.getGrade() > this->getGradeToExecute())
        throw GradeTooLowException();

    std::cout << BLUE << "Bzzzzzzz... drilling noise... \n" << RESET;

    srand(time(NULL));

    if(rand() % 2 == 0)
    {
        std::cout << GREEN << target << " has been robotomized succesfully\n" << RESET;
    }
    else
    {
        std::cout << RED << target << " has failed to be robotomized\n" << RESET;
    }
}

RobotomyRequestForm::~RobotomyRequestForm()
{}