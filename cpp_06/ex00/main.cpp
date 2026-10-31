#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./convert <literal>" << std::endl;
        return (1);
    }
    
    std::string literal = argv[1];

    t_cast_type type = getType(literal);
    (void)type;

    ScalarConverter::convert(literal);

    return (0);
}