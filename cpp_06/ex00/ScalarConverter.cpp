#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal)
{
    (void)literal;
}

ScalarConverter::ScalarConverter()
{
}
ScalarConverter::ScalarConverter(ScalarConverter const &other)
{
    *this = other;
}
ScalarConverter &ScalarConverter ::operator=(ScalarConverter const &other)
{
    (void)other;
    return (*this);
}

ScalarConverter::~ScalarConverter()
{
}
