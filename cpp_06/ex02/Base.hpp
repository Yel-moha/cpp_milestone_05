#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

class Base
{
public:
    Base();
    virtual ~Base();
    virtual void identify() const;
};