#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target)
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

const char* ShrubberyCreationForm::FileOpenException::what() const throw()
{
    return "Failed to open the file for writing.";
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