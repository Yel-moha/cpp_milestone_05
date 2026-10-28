#include "Bureaucrat.hpp"
#include "AForm.hpp"


Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if(this != &other)
        grade = other.grade;
    return(*this);
}

Bureaucrat::Bureaucrat(const std::string name, int grade): name(name), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
Bureaucrat::Bureaucrat() : name (""), grade(150)
{
}
Bureaucrat::Bureaucrat(const std::string name) : name (name), grade (150)
{
}

Bureaucrat::Bureaucrat(int grade) : name(""), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other): name(other.name), grade(other.grade)
{
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
    if (this->grade == 1)
        throw GradeTooHighException();
    this->grade--;
}

void Bureaucrat::decrementGrade()
{
    if(this->grade == 150)
        throw GradeTooLowException();

    this->grade++;
}

void Bureaucrat::signForm(AForm &form) const
{
	try
	{
		form.beSigned(*this);
		std::cout << name << " signed " << form.getName() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << name << " couldn't sign " << form.getName()
			<< " because " << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(AForm const& form) const
{
    try
    {
        form.execute(*this);
        std::cout << *this << " executed " << form << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << *this << " couldn't execute " << form
                  << " because " << e.what() << std::endl;
    }
}

Bureaucrat::~Bureaucrat()
{
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat& obj)
{
    out << obj.getName() << ", bureaucrat grade " << obj.getGrade() << '\n';
    return out;
}
