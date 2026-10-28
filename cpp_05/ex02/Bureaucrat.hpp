#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class AForm;

class Bureaucrat {
	private:
		const std::string name;
		int grade; // A grade that ranges from 1
		// (highest possible grade) to 150 (lowest possible grade).

	public:
		Bureaucrat();
        Bureaucrat(const std::string name);
        Bureaucrat(int grade);
        Bureaucrat(const std::string name, int grade);
        Bureaucrat(const Bureaucrat &other);
        Bureaucrat &operator=(const Bureaucrat &other);

        
		std::string getName() const;
		int getGrade() const;


		void incrementGrade();
		void decrementGrade();
		void signForm(AForm &form) const;
        void executeForm(AForm const & form) const;

		class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
		};
        ~Bureaucrat();
};

std::ostream& operator<<(std::ostream &out, const Bureaucrat& obj);

#endif
