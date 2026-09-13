#include "Bureaucrat.hpp"

//Constructors
Bureaucrat::Bureaucrat(): name(""), grade(150)
{
    std::cout << "Default constructor\n";
}

Bureaucrat::Bureaucrat(int grade): name(""), grade(150)
{
    std::cout << "Grade param constructor\n";

    if(grade < 1)
        throw GradeToHigh();
    if(grade > 150)
        throw GradeToLow();

    this->grade = grade;
}

Bureaucrat::Bureaucrat(const std::string name): name(name), grade(150)
{
    std::cout << "Name param constructor\n";
}

Bureaucrat::Bureaucrat(const std::string name, int grade): name(name), grade(150)
{
    std::cout << "Name and grade param constructor\n";

    if(grade < 1)
        throw GradeToHigh();
    if(grade > 150)
        throw GradeToLow();

    this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other): name(other.name), grade(other.grade)
{
    std::cout << "Copy constructor\n";
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &other)
{
    if(this == &other)
        return *this;

    this->grade = other.grade;
    return *this;
}


//Getters
std::string Bureaucrat::getName() const
{
    return this->name;
}

int Bureaucrat::getGrade() const
{
    return this->grade;
}

//Methods
void Bureaucrat::incrementGrade()
{
    this->grade--;

    if(this->grade < 1)
        throw GradeToHigh();
}

void Bureaucrat::decrementGrade()
{
    this->grade++;
    
    if(this->grade > 150)
        throw GradeToLow();
}

void Bureaucrat::signForm(AForm& form)
{
    try{
        form.beSigned(*this);
        std::cout << GREEN << this->name << " signed " << form.getName() << '\n' << RESET;
    }
    catch(std::exception& e)
    {
        std::cout << RED << this->name << " couldn't be signed for " << form.getName() << " because " << e.what() << '\n' << RESET;
    }
}

void Bureaucrat::executeForm(const AForm& form) const
{
    try{
        form.execute(*this);
        std::cout << GREEN << this->name << " executed " << form.getName() << ".\n" << RESET;
    }
    catch (std::exception& e)
    {
        std::cout << RED << this->name << " couldn't execute form " << form.getName() << " because " << e.what() << '\n' << RESET;
    }
}

//Destructor
Bureaucrat::~Bureaucrat()
{
    std::cout << "Destructor!\n";
}

//Insertion operator
std::ostream& operator<<(std::ostream &out, const Bureaucrat& obj)
{
    out << obj.getName() << ", bureaucrat grade " << obj.getGrade() << '\n';
    return out;
}
