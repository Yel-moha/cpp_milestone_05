#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>

//Definisco struttura contenete tipi di cast

typedef enum e_cast_type
{
    OTHER = 0,
    CHAR = 1,
    INT = 2,
    FLOAT = 3,
    DOUBLE = 4,
    NONE = -1
} t_cast_type;

class ScalarConverter
{
    private:
        
    public:
        static void convert(const std::string& literal);
        ScalarConverter();
        ScalarConverter(ScalarConverter const &other);
        ScalarConverter &operator=(ScalarConverter const &other);
        ~ScalarConverter();
};

void covertToChar(const std::string& literal);
void covertToInt(const std::string& literal);
void covertToFloat(const std::string& literal);
void covertToDouble(const std::string& literal);
void notConvert(const std::string& literal);
t_cast_type getType(std::string &literal);
#endif