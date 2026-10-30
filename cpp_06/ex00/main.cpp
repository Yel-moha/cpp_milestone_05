#include "ScalarConverter.hpp"

int main()
{
    std::string literal = "ciao";

    t_cast_type type = getType(literal);
    (void)type;

    ScalarConverter::convert(literal);

    return (0);
}