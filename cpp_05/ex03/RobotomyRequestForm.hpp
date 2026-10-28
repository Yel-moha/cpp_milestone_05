#ifndef ROBOT_MY_REQUEST_FORM_HPP
#define ROBOT_MY_REQUEST_FORM_HPP

#include "AForm.hpp"
#include <fstream>

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;

        virtual void executeAction() const;
    
    public:
        RobotomyRequestForm(std::string const &target);
        RobotomyRequestForm(RobotomyRequestForm const &other);
        RobotomyRequestForm &operator=(RobotomyRequestForm const &other);
        virtual ~RobotomyRequestForm();

        std::string getTarget() const;
};
#endif
