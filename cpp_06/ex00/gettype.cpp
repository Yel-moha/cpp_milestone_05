#include "ScalarConverter.hpp"


t_cast_type getType(std::string &literal)
{
    size_t lenlit = literal.length();
    std::cout << "literal e' lunga " << lenlit << "\n";
    return (INT);
}