#include "ScalarConverter.hpp"

void covertToChar(const std::string& literal)
{
    if (literal.length() == 1 && std::isprint(literal[0]))
    {
        char c = literal[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
    }
    else
    {
        std::cout << "char: Non displayable" << std::endl;
        std::cout << "int: Non displayable" << std::endl;
        std::cout << "float: Non displayable" << std::endl;
        std::cout << "double: Non displayable" << std::endl;
    }
}

void covertToInt(const std::string& literal)
{
    try
    {
        int value = std::atoi(literal.c_str());
        std::cout << "char: ";
        if (value >= 0 && value <= 127 && std::isprint(value))
            std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;

        std::cout << "int: " << value << std::endl;
        std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: Invalid integer literal." << std::endl;
    }
}

void covertToFloat(const std::string& literal)
{
   float value = static_cast<float>(std::atof(literal.c_str()));
    std::cout << "char: ";
    if (value >= 0 && value <= 127 && std::isprint(static_cast<int>(value)))
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;
    
    std::cout << "int: ";
    if (value < static_cast<float>(INT_MIN) || value > static_cast<float>(INT_MAX))
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;
    
    std::cout << "float: ";
    if (value < -FLT_MAX || value > FLT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << value << "f" << std::endl;
    
    std::cout << "double: ";
    if (value < -DBL_MAX || value > DBL_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<double>(value) << std::endl;
}

void covertToDouble(const std::string& literal)
{
   double value = std::atof(literal.c_str());
    std::cout << "char: ";
    if (value >= 0 && value <= 127 && std::isprint(static_cast<int>(value)))
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;
    
    std::cout << "int: ";
    if (value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX))
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;
    
    std::cout << "float: ";
    if (value < static_cast<double>(-FLT_MAX) || value > static_cast<double>(FLT_MAX))
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<float>(value) << "f" << std::endl;
    
    std::cout << "double: ";
    if (value < -DBL_MAX || value > DBL_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << value << std::endl;
}

void notConvert(const std::string& literal)
{
    if(literal == "nan" || literal == "nanf" )  
    {
        std::cout << "char: impossibile" <<std::endl;
        std::cout << "int: impossibile" <<std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;            
    }
    else if(literal == "+inf" || literal == "+inff")
    {
        std::cout << "char : impossibile" <<std::endl;
        std::cout << "int: impossibile" <<std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else if(literal == "-inf" || literal == "-inff")
    {
        std::cout << "char : impossibile" <<std::endl;
        std::cout << "int : impossibile" <<std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}