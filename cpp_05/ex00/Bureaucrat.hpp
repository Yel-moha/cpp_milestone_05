#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>

class Bureaucrat {
	private:
		const std::string name;
		int grade; // A grade that ranges from 1
		// (highest possible grade) to 150 (lowest possible grade).

	public:
		Bureaucrat();
		std::string getName() const;
		int getGrade() const;
		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException {
		};

		class GradeTooLowException {
		};
};

#endif