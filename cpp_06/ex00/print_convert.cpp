#include "ScalarConverter.hpp"

void covertToChar(const std::string& literal)
{
    char c = literal.length() == 1 ? literal[0] : literal[1];
    int value = static_cast<unsigned char>(c);

    std::cout << "char: ";
    if (value > 127)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(c)))
    {
        std::cout << "'" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
    }
    else
        std::cout << "Non displayable" << std::endl;
}

void covertToInt(const std::string& literal)
{
    long value = std::atol(literal.c_str());
    std::cout << "char: ";
    if (value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(value)))
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;
    
    std::cout << "int: ";
    if(value < INT_MIN || value > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;
    
    std::cout << "float: ";
    if(value < -FLT_MAX || value > FLT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<float>(value) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void covertToFloat(const std::string& literal)
{

    double value = std::atof(literal.c_str());
    bool tol = std::fabs(value - static_cast<long>(value)) < 0.0000000000001;
    std::cout << "char: ";
    if (value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(value)))
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
    {
        // FIXME: controllare formato richiesto per interi in float (es. 42.0f vs 42f).
        std::cout << value ;
        if(tol)
            std::cout << ".0f" <<std::endl;
        else
            std::cout << "f" << std::endl;
    }
    
    std::cout << "double: " << static_cast<double>(value) << (tol ? ".0" : "") << std::endl;
}

void covertToDouble(const std::string& literal)
{
    // FIXME: valutare parser piu robusto rispetto ad atof.
    double value = std::atof(literal.c_str());
    std::cout << "char: ";
    if (value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(value)))
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
    // FIXME: controllo ridondante sul range double; chiarire gestione esplicita di inf/nan.
    if (value < -DBL_MAX || value > DBL_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << value << std::endl;
}

void notConvert(const std::string& literal)
{
    if(literal == "nan" || literal == "nanf" )  
    {
        std::cout << "char: impossible" <<std::endl;
        std::cout << "int: impossible" <<std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;            
    }
    else if(literal == "+inf" || literal == "+inff")
    {
        std::cout << "char : impossible" <<std::endl;
        std::cout << "int: impossible" <<std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else if(literal == "-inf" || literal == "-inff")
    {
        std::cout << "char : impossible" <<std::endl;
        std::cout << "int : impossible" <<std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}