#include "RobotomyRequestForm.hpp"
#include <cstdlib>


RobotomyRequestForm::RobotomyRequestForm(std::string const &target)
    : AForm("RobotomyRequestForm", 72, 45), target(target)
{    
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other)
    : AForm(other), target(other.target)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(
    RobotomyRequestForm const &other)
{
    if (this != &other)
    {
        AForm::operator=(other); // copia lo stato ereditato
        target = other.target;   // oppure _target = other._target
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

std::string RobotomyRequestForm::getTarget() const
{
    return target;
}

void RobotomyRequestForm::executeAction() const
{
    std::cout << "Drilling noises..." << std::endl;
    if (rand() % 2 == 0)
        std::cout << target << " has been robotomized successfully." << std::endl;
    else
        std::cout << "Robotomy failed on " << target << "." << std::endl;
}