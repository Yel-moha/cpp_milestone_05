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

static void ScalarConverter::convert(const std::string& literal)
{
    t_cast_type type = getType(literal);
    switch (type)
    {
        case CHAR:
            covertToChar(literal);
            break;
        case INT:
            covertToInt(literal);
            break;
        case FLOAT:
            covertToFloat(literal);
            break;
        case DOUBLE:
            covertToDouble(literal);
            break;
        default:
            std::cout << "Error: Invalid literal type." << std::endl;
            break;
    }
}