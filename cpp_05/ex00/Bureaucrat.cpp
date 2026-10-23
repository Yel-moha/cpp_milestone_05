#include "Bureaucrat.hpp"


Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if(this != &other)
        grade = other.grade;
    return(*this);
}

Bureaucrat::Bureaucrat(const std::string name, int grade): name(name), grade(grade)
{
    std::cout << "Name and grade param constructor" << std::endl;
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
Bureaucrat::Bureaucrat() : name (""), grade(150)
{
     std::cout << "Default constructor\n";
}
Bureaucrat::Bureaucrat(const std::string name) : name (name), grade (150)
{
    std::cout << "Name constructor" << std::endl;
}

Bureaucrat::Bureaucrat(int grade) : name(""), grade(grade)
{
    std::cout << "Grade param constructor" << std::endl;
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other): name(other.name), grade(other.grade)
{
    std::cout << "Copy constructor" << std::endl;
}

std::string Bureaucrat::getName() const
{
    return this->name;
}

int Bureaucrat::getGrade() const
{
    return this->grade;
}

void Bureaucrat::incrementGrade()
{
    this->grade--;

    if (this->grade < 1)
        throw GradeTooHighException();
}

void Bureaucrat::decrementGrade()
{
    this->grade++;

    if(this->grade > 150)
        throw GradeTooLowException();
}
Bureaucrat::~Bureaucrat()
{
    std::cout << "Destructor!" << std::endl;
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat& obj)
{
    out << obj.getName() << ", bureaucrat grade " << obj.getGrade() << '\n';
    return out;
}
