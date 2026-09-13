#ifndef __AFORM_HPP__
#define __AFORM_HPP__

#include <iostream>
#include <string>
#include <fstream>

class Bureaucrat;

class AForm{

    public:
        //constructors
        AForm();
        AForm(const std::string name, int gradeToSign, int gradeToExecute);
        AForm(const AForm& other);
        AForm& operator=(const AForm& other);

        //getters
        std::string getName() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        bool getIsSigned() const;

        //methods
        void beSigned(const Bureaucrat& bureaucrat);

        //pure virtual function
        virtual void execute(Bureaucrat const & executor) const = 0;

        //exceptions
        class GradeTooLowException : public std::exception{
            virtual const char* what() const throw()
            {
                return "Grade is too low!";
            }
        };

        class GradeTooHighException : public std::exception{
            virtual const char* what() const throw()
            {
                return "Grade is too high!";
            }
        };

        class FormNotSignedException : public std::exception{
            virtual const char* what() const throw()
            {
                return "Form is not signed!";
            }
        };

        //destructor
        virtual ~AForm();

    private:
        const std::string name;
        bool isSigned;
        const int gradeToSign;
        const int gradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const AForm&  aform);

#endif