#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target):
    AForm("Shrubbery Creation Form", 145, 137), target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other):
    AForm(other), target(other.target)
{}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if(this != &other)
    {
        AForm::operator=(other);
        target = other.target;
    }

    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
    if(!this->getIsSigned())
        throw FormNotSignedException();

    if(executor.getGrade() > this->getGradeToExecute())
    {
        throw GradeTooLowException();
    }

    std::string filename = this->target + "_shrubbery";
    std::ofstream file(filename.c_str());

    if(!file.is_open())
        throw std::runtime_error("Cannot create file");

    file << "              _{\\{__{\\{\\/)}/}/__\n"
         << "             {/{/\\}{/{/\\}(\\}{/\\} _\n"
         << "            {/{/\\}{/{/\\}(_)\\}{/{/\\}  _\n"
         << "         {\\{/(\\}\\}{/{/\\}\\}{/){\\/\\}\\} /\\}\n"
         << "        {/{/(_)/}{\\{/)\\}{\\(_){/}/}/}/}\n"
         << "       _{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}\n"
         << "      {/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}\n"
         << "      _{\\{/{\\{/(_)\\}/}{/{/{/\\}\\})\\}{/\\}\n"
         << "     {/{/{\\{\\(/}{/{\\{\\{\\/})/}{\\(_)/}/}\\}\n"
         << "      {\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}\n"
         << "       {/{\\{\\/}{/{\\{\\{\\/}/}{\\{\\/}/}\\}(_)\n"
         << "      {/{\\{\\/}{/){\\{\\{\\/}/}{\\{\\(/}/}\\}/}\n"
         << "       {/{\\{\\/}(_){\\{\\{\\(/}/}{\\(_)/}/}\\}\n"
         << "         {/({/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}\n"
         << "          (_){/{\\/)}{\\{\\/}/}{\\{\\)/}/}(_)\n"
         << "            {/{/{\\{\\/}{/{\\{\\{\\(_)/}\n"
         << "             {/{\\{\\{\\/}/}{\\{\\\\\\}/}\n"
         << "              {){/ {\\/}{\\/} \\}\\}\n"
         << "              (_)  \\.-'.-/\n"
         << "          __...--- |'-.-'| --....__\n"
         << "   _...--\"   .-'   |'-.-'|  ' -.  \"\"--...__\n"
         << " -\"    ' .  . '    |.'-._| '  . .  '  jro\n"
         << " .  '-  '    .--'  | '-.'|    .  '  . '\n"
         << "          ' ..     |'-_.-|\n"
         << "  .  '  .       _.-|-._ -|-._  .  '  .\n"
         << "              .'   |'- .-|   '.\n"
         << "  ..-'   ' .  '.   `-._.-'   .'  '  - .\n"
         << "   .-' '        '-._______.-'     '  .\n"
         << "        .      ~,\n"
         << "    .       .   |\\   .    ' '-.\n"
         << "    ___________/  \\____________\n"
         << "   /  Why is it, when you want \\\n"
         << "  |  something, it is so damn   |\n"
         << "  |    much work to get it?     |\n"
         << "   \\___________________________/\n";

    file.close();
}