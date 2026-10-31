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

static bool isDouble(const std::string &literal)
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

static bool isChar(const std::string &literal)
{
    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return (true);
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return (true);
    return (false);
}

static bool isSpecial(const std::string &literal)
{
    return (literal == "nan" || literal == "+inf" || literal == "-inf" ||
            literal == "nanf" || literal == "+inff" || literal == "-inff");
}

t_cast_type getType(std::string &literal)
{
    size_t  dot = literal.find('.');
    size_t  f = literal.find('f');
    if(dot == std::string::npos && f == std::string::npos)
    {
        if (isChar(literal))
            return (CHAR);
        else if (isInt(literal))
            return (INT);
        else
            return (NONE);
    }
    else if(dot != std::string::npos && f == std::string::npos)
    {
        if (isDouble(literal))
            return (DOUBLE);
        else
            return (NONE);
    }
    else if(dot != std::string::npos && f != std::string::npos && f == literal.length() - 1)
    {
        if (isFloat(literal))
            return (FLOAT);
        else
            return (NONE);
    }
    else
        return (NONE);
}