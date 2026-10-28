#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include "AForm.hpp"

class Intern
{
    public:
        Intern();
        Intern(const Intern& other);
        Intern& operator=(const Intern& other);
        ~Intern();
        AForm* makeForm(const std::string& formName, const std::string& target) const;

    private:
        static AForm* createShrubbery(const std::string& target);
        static AForm* createRobotomy(const std::string& target);
        static AForm* createPresidentialPardon(const std::string& target);
};  

#endif