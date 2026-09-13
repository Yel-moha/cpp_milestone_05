#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <iostream>
#include <string>

class Bureaucrat;

class Form{

    public:
        //constructors
        Form();
        Form(const std::string name, int gradeToSign, int gradeToExecute);
        Form(const Form& other);
        Form& operator=(const Form& other);

        //getters
        std::string getName() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        bool getIsSigned() const;

        //methods
        void beSigned(const Bureaucrat& bureaucrat);

        //exceptions
        class GradeTooLowException : public std::exception{
            virtual const char* what() const throw()
            {
                return "Grade is too low to be signed!";
            }
        };

        class GradeTooHighException : public std::exception{
            virtual const char* what() const throw()
            {
                return "Grade is too high to be signed!";
            }
        };

        //destructor
        ~Form();

    private:
        const std::string name;
        bool isSigned;
        const int gradeToSign;
        const int gradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const Form&  form);

#endif