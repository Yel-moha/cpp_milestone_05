#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

#include "AForm.hpp"
#include "Bureaucrat"

class ShrubberyCreationForm : public AForm
{
    private:
        std::string target;
    
    protected:
        virtual void executeAcion() const;
    
    public:
        ShrubberyCreationForm(std::string const &target);
        ShrubberyCreationForm(ShrubberyCreationForm const &other);
        ShrubberyCreationForm &operator=(ShrubberyCreationForm const &other);
        virtual ~ShrubberyCreationForm();

        std::string getTarget() const;
};

#endif