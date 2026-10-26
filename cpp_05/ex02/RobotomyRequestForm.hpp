#ifndef ROBOT_MY_REQUEST_FORM_HPP
#define ROBOT_MY_REQUEST_FORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;
    
    protected:
        virtual void executeAcion() const;
    
    public:
        RobotomyRequestForm(std::string const &target);
        RobotomyRequestForm(RobotomyRequestForm const &other);
        RobotomyRequestForm &operator=(RobotomyRequestForm const &other);
        virtual ~RobotomyRequestForm();
};
#endif