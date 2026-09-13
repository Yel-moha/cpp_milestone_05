#ifndef __ROBOTOMY_REQUEST_FORM_HPP__
#define __ROBOTOMY_REQUEST_FORM_HPP__

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <ctime>
#include <cstdlib>

class RobotomyRequestForm : public AForm{
    public:
        RobotomyRequestForm(const std::string target);
        RobotomyRequestForm(const RobotomyRequestForm& other);
        RobotomyRequestForm& operator=(const RobotomyRequestForm& other);

        void execute(const Bureaucrat& executor) const;

        ~RobotomyRequestForm();
    private:
        std::string target;
};


#endif