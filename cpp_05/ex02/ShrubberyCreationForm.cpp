#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
    : AForm("ShrubberyCreationForm", 145, 45), target(target)
{  
}
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other)
    : AForm(other), target(other.target)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(
    ShrubberyCreationForm const &other)
{
    if (this != &other)
    {
        AForm::operator=(other); // copia lo stato ereditato
        target = other.target;   // oppure _target = other._target
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

std::string ShrubberyCreationForm::getTarget() const
{
    return target;
}

void ShrubberyCreationForm::executeAction() const
{
    std::ofstream output((target + "_shrubbery").c_str());
    if (!output)
        throw FileOpenException();

    output << "       _-_" << std::endl;
    output << "    /~~   ~~\\" << std::endl;
    output << " /~~         ~~\\" << std::endl;
    output << "{               }" << std::endl;
    output << " \\  _-     -_  /" << std::endl;
    output << "   ~  \\\\ //  ~" << std::endl;
    output << "_- -   | | _- _" << std::endl;
    output << "  _ -  | |   -_" << std::endl;
    output << "      // \\\\" << std::endl;

    output.close();
}