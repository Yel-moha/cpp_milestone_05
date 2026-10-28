#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name(""), is_signed(false), sign_grade(150), exec_grade(150)
{
}

Form::Form(const std::string &name, int sign_grade, int exec_grade)
	: name(name), is_signed(false), sign_grade(sign_grade), exec_grade(exec_grade)
{
	if (sign_grade < 1 || exec_grade < 1)
		throw GradeTooHighException();
	if (sign_grade > 150 || exec_grade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &other)
	: name(other.name), is_signed(other.is_signed),
	  sign_grade(other.sign_grade), exec_grade(other.exec_grade)
{
}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
		is_signed = other.is_signed;
	return *this;
}

Form::~Form()
{
}

std::string Form::getName() const
{
	return name;
}

bool Form::getIsSigned() const
{
	return is_signed;
}

int Form::getSignGrade() const
{
	return sign_grade;
}

int Form::getExecGrade() const
{
	return exec_grade;
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > sign_grade)
		throw GradeTooHighException();
	is_signed = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return "form grade is too high";
}

const char *Form::GradeTooLowException::what() const throw()
{
	return "form grade is too low";
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << form.getName() << ", form is "
		<< (form.getIsSigned() ? "signed" : "not signed")
		<< ", grade required to sign: " << form.getSignGrade()
		<< ", grade required to execute: " << form.getExecGrade();
	return out;
}
