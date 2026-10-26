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

protected:
	/*
	protected è una buona scelta per executeAction: è visibile alle classi
	derivate, ma non è un'operazione che il codice cliente dovrebbe chiamare
	direttamente. Anche public è tecnicamente valido, ma esporrebbe un'azione
	senza i controlli di execute().
	*/
	virtual void executeAction() const = 0;
	
public:
	AForm();
	AForm(const std::string &name, int sign_grade, int exec_grade);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm();

	std::string getName() const;
	bool getIsSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	void beSigned(const Bureaucrat &bureaucrat);
	void execute(Bureaucrat const & executor) const;




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

	/*
	class FormNotSignedException : public std::exception
	{
	public:
		const char *what() const throw();
	}
		*/
};

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif
