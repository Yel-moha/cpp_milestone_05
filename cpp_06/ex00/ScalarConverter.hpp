#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>


class ScalarConverter
{
    private:
        static std::string literal;

    public:
        static void convert(const std::string& literal);
}

#endif