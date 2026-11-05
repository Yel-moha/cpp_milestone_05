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

static bool isDecimal(const std::string &literal, size_t length)
{
    if(length == 0)
        return (false);
    size_t i = 0;
    if (literal[i] == '-' || literal[i] == '+')
        i++;
    bool hasPoint = false;
    bool hasMantissaDigit = false;
    while (i < length && literal[i] != 'e' && literal[i] != 'E')
    {
        if (std::isdigit(literal[i]))
            hasMantissaDigit = true;
        else if (literal[i] == '.' && !hasPoint)
            hasPoint = true;
        else
            return (false);
        i++;
    }
    if (!hasMantissaDigit)
        return (false);
    if (i < length)
    {
        i++;
        if (i < length && (literal[i] == '-' || literal[i] == '+'))
            i++;
        size_t exponentStart = i;
        while (i < length && std::isdigit(literal[i]))
            i++;
        if (i == exponentStart)
            return (false);
    }
    return (i == length);
}

static bool isFloat(const std::string &literal)
{
    if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
        return (false);
    return (isDecimal(literal, literal.length() - 1));
}

static bool isDouble(const std::string &literal)
{
    return (isDecimal(literal, literal.length()));
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

t_cast_type getType(const std::string &literal)
{
    if (isSpecial(literal))
        return (SPECIAL);
    if (isChar(literal))
        return (CHAR);
    if (isInt(literal))
        return (INT);
    if (isFloat(literal))
        return (FLOAT);
    if (isDouble(literal))
        return (DOUBLE);
    return (NONE);
}