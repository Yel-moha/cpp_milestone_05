#ifndef AForm_HPP
#define AForm_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm
{
private:
	const std::string name;
	bool is_signed;
	const int sign_grade;
	const int exec_grade;

public:
	AForm();
	AForm(const std::string &name, int sign_grade, int exec_grade);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	~AForm();

	std::string getName() const;
	bool getIsSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	virtual void beSigned(const Bureaucrat &bureaucrat) = 0;

	class GradeTooHighException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif
