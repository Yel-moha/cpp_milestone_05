#include "Form.hpp"
#include "Bureaucrat.hpp"

//Constructors
Form::Form(): name(""), isSigned(false), gradeToSign(150), gradeToExecute(150)
{
    std::cout << "Deafult constructor.\n";
}

Form::Form(const std::string name, int gradeToSign, int gradeToExecute):
name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    std::cout << "3 param cnostructor.\n";

    if(gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if(gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other): name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign),
gradeToExecute(other.gradeToExecute)
{
    std::cout << "Copy constructor.\n";
}

Form& Form::operator=(const Form& other)
{
    if(this == &other)
        return *this;

    this->isSigned = other.isSigned;

    return *this;
}


//Getters
std::string Form::getName() const
{
    return this->name;
}

int Form::getGradeToSign() const
{
    return this->gradeToSign;
}

int Form::getGradeToExecute() const
{
    return this->gradeToExecute;
}

bool Form::getIsSigned() const
{
    return this->isSigned;
}

//Methods
void Form::beSigned(const Bureaucrat& bureaucrat)
{
    if(bureaucrat.getGrade() > this->gradeToSign)
        throw GradeTooLowException();
    else
        this->isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
    out << "Form: " << form.getName() << '\n'
        << "Signed: " << (form.getIsSigned() ? "Yes" : "No") << '\n'
        << "Grade To Sign: " << form.getGradeToSign() << '\n'
        << "Grade To Execute: " << form.getGradeToExecute() << '\n';
    
    return out;
}

Form::~Form()
{
    std::cout << "Destructor\n";
}