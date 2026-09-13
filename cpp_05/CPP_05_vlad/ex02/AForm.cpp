#include "AForm.hpp"
#include "Bureaucrat.hpp"

//Constructors
AForm::AForm(): name(""), isSigned(false), gradeToSign(150), gradeToExecute(150)
{
    std::cout << "Deafult constructor.\n";
}

AForm::AForm(const std::string name, int gradeToSign, int gradeToExecute):
name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    std::cout << "3 param cnostructor.\n";

    if(gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if(gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other): name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign),
gradeToExecute(other.gradeToExecute)
{
    std::cout << "Copy constructor.\n";
}

AForm& AForm::operator=(const AForm& other)
{
    if(this == &other)
        return *this;

    this->isSigned = other.isSigned;

    return *this;
}


//Getters
std::string AForm::getName() const
{
    return this->name;
}

int AForm::getGradeToSign() const
{
    return this->gradeToSign;
}

int AForm::getGradeToExecute() const
{
    return this->gradeToExecute;
}

bool AForm::getIsSigned() const
{
    return this->isSigned;
}

//Methods
void AForm::beSigned(const Bureaucrat& bureaucrat)
{
    if(bureaucrat.getGrade() > this->gradeToSign)
        throw GradeTooLowException();
    else
        this->isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const AForm& aform)
{
    out << "Form: " << aform.getName() << '\n'
        << "Signed: " << (aform.getIsSigned() ? "Yes" : "No") << '\n'
        << "Grade To Sign: " << aform.getGradeToSign() << '\n'
        << "Grade To Execute: " << aform.getGradeToExecute() << '\n';
    
    return out;
}

AForm::~AForm()
{
    std::cout << "Destructor\n";
}