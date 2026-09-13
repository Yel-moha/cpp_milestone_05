#ifndef __PRESIDENTIAL_PARDON_FORM_HPP
#define __PRESIDENTIAL_PARDON_FORM_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm {
    public:
        PresidentialPardonForm(const std::string target);
        PresidentialPardonForm(const PresidentialPardonForm& other);
        PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

        void execute(const Bureaucrat& executor) const;

        ~PresidentialPardonForm();

    private:
        std::string target;
};

#endif