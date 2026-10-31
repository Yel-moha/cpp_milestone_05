#include "ScalarConverter.hpp"

static bool isInt(const std::string &literal)
{
    size_t lenlit = literal.length();
    if(lenlit == 0)
        return (false);
    size_t i = 0;
    if (literal[i] == '-' || literal[i] == '+')
        i++;
    for(; i < lenlit; i++)
    {
        if (!std::isdigit(literal[i]))
            return (false);
    }
    return (true);
}

static bool isFloat(const std::string &literal)
{
    size_t lenlit = literal.length();
    if(lenlit == 0)
        return (false);
    size_t i = 0;
    if (literal[i] == '-' || literal[i] == '+')
        i++;
    bool hasDecimalPoint = false;
    for(; i < lenlit; i++)
    {
        if (literal[i] == '.')
        {
            if (hasDecimalPoint)
                return (false);
            hasDecimalPoint = true;
        }
        else if (!std::isdigit(literal[i]))
            return (false);
    }
    return (true);  
}

t_cast_type getType(std::string &literal)
{
    size_t lenlit = literal.length();
    std::cout << "literal e' lunga " << lenlit << "\n";
    return (INT);
}