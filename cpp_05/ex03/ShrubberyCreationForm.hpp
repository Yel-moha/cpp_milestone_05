#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

#include "AForm.hpp"
#include <string>

class ShrubberyCreationForm : public AForm
{
private:
    std::string target;

    void executeAction() const;

public:
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    virtual ~ShrubberyCreationForm();

    std::string getTarget() const;
    
    class FileOpenException : public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
};

#endif