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
        int value = std::stoi(literal);
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
    try
    {
        float value = std::stof(literal);
        std::cout << "char: ";
        if (value >= 0 && value <= 127 && std::isprint(static_cast<int>(value)))
            std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;

        std::cout << "int: " << static_cast<int>(value) << std::endl;
        std::cout << "float: " << value << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(value) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: Invalid float literal." << std::endl;
    }
}

void covertToDouble(const std::string& literal)
{
    try
    {
        double value = std::stod(literal);
        std::cout << "char: ";
        if (value >= 0 && value <= 127 && std::isprint(static_cast<int>(value)))
            std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;

        std::cout << "int: " << static_cast<int>(value) << std::endl;
        std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
        std::cout << "double: " << value << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: Invalid double literal." << std::endl;
    }
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