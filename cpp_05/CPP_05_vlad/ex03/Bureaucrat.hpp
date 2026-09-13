#ifndef __BUREAUCRAT_HPP__
#define __BUREAUCRAT_HPP__

#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define BLUE "\e[0;34m"
#define RESET "\e[0m"

#include <iostream>
#include <cstring>
#include <string>
#include "AForm.hpp"

class Bureaucrat {
    public:

        //constructors
        Bureaucrat();
        Bureaucrat(const std::string name);
        Bureaucrat(int grade);
        Bureaucrat(const std::string name, int grade);
        Bureaucrat(const Bureaucrat &other);
        Bureaucrat& operator=(const Bureaucrat &other);

        //getters
        std::string getName() const;
        int getGrade() const;

        //incrementing/decrementing functions
        void incrementGrade();
        void decrementGrade();

        //exceptions
        class GradeToHigh : public std::exception {

            virtual const char* what() const throw() {
                return "Grade is to High!";
            }

        };

        class GradeToLow : public std::exception {

            virtual const char* what() const throw() {
                return "Grade is to Low!";
            }

        };

        void signForm(AForm& form);
        void executeForm(const AForm& form) const;

        //desctructor
        ~Bureaucrat();

    private:
        const std::string name;
        int grade;
};

std::ostream& operator<<(std::ostream &out, const Bureaucrat& obj);

#endif