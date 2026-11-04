#include "ScalarConverter.hpp"

/* ************************************************************************** */
/*                          HELPER DI STAMPA                                  */
/* Ogni helper stampa UNA riga. Le funzioni convertTo... convertono la        */
/* stringa nel suo tipo reale e poi passano il valore (con cast esplicito)    */
/* a questi helper.                                                           */
/* ************************************************************************** */

// Aggiunge ".0" se il numero stampato non ha gia' un punto, un esponente
// (notazione scientifica, es. "1e+08") o se non e' inf/nan.
static std::string addPointZero(const std::string &s)
{
    if (s.find('.') == std::string::npos && s.find('e') == std::string::npos
        && s.find("inf") == std::string::npos && s.find("nan") == std::string::npos)
        return (s + ".0");
    return (s);
}

static void printChar(double value)
{
    std::cout << "char: ";
    if (value != value || value < 0 || value > 127) // value != value -> nan
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(value)))
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;
}

static void printInt(double value)
{
    std::cout << "int: ";
    // Confronto in double: INT_MIN e INT_MAX sono rappresentabili esattamente
    // in un double (in un float no: static_cast<float>(INT_MAX) = 2147483648).
    if (value != value || value < static_cast<double>(INT_MIN)
        || value > static_cast<double>(INT_MAX))
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;
}

static void printFloat(float value)
{
    std::ostringstream oss;
    oss << value;
    std::cout << "float: " << addPointZero(oss.str()) << "f" << std::endl;
}

static void printDouble(double value)
{
    std::ostringstream oss;
    oss.precision(DBL_DIG); // 15 cifre significative: 2147483647 resta intero
    oss << value;
    std::cout << "double: " << addPointZero(oss.str()) << std::endl;
}

static void printAllImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

/* ************************************************************************** */
/*                          CONVERSIONI                                       */
/* ************************************************************************** */

void convertToChar(const std::string& literal)
{
    // "a" oppure "'a'"
    char c = literal.length() == 1 ? literal[0] : literal[1];

    printChar(static_cast<double>(static_cast<unsigned char>(c)));
    printInt(static_cast<double>(c));
    printFloat(static_cast<float>(c));
    printDouble(static_cast<double>(c));
}

void convertToInt(const std::string& literal)
{
    errno = 0;
    long value = std::strtol(literal.c_str(), NULL, 10);

    // errno == ERANGE -> il numero non entra neanche in un long.
    // Il secondo controllo serve perche' long (64 bit) e' piu' grande di int.
    if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
    {
        // Non e' un int valido, ma come double/float puo' esistere
        // (es. 2147483648): lo rileggo come double, che stampera'
        // "int: impossible" da solo.
        convertToDouble(literal);
        return ;
    }

    int i = static_cast<int>(value);
    printChar(static_cast<double>(i));
    printInt(static_cast<double>(i));
    printFloat(static_cast<float>(i));
    printDouble(static_cast<double>(i));
}

void convertToFloat(const std::string& literal)
{
    errno = 0;
    // strtof e' C99 (non C++98): uso strtod, che e' C89 e quindi C++98.
    // strtod legge "42.5f" e si ferma sulla 'f' (non e' un errore).
    double tmp = std::strtod(literal.c_str(), NULL);

    // ERANGE arriva sia per overflow (ritorna +-HUGE_VAL) sia per underflow
    // (numero troppo vicino a 0, ritorna ~0). Solo l'overflow e' un errore.
    // strtod controlla il range del DOUBLE: il range del FLOAT (molto piu'
    // piccolo, ~3.4e38) lo controllo io a mano con FLT_MAX.
    if ((errno == ERANGE && (tmp > DBL_MAX || tmp < -DBL_MAX))
        || tmp > static_cast<double>(FLT_MAX)
        || tmp < static_cast<double>(-FLT_MAX))
    {
        printAllImpossible();
        return ;
    }

    // Ora sono sicuro che entra in un float: questo e' il "tipo reale".
    float value = static_cast<float>(tmp);

    printChar(static_cast<double>(value));
    printInt(static_cast<double>(value));
    printFloat(value);
    printDouble(static_cast<double>(value));
}

void convertToDouble(const std::string& literal)
{
    errno = 0;
    double value = std::strtod(literal.c_str(), NULL);

    if (errno == ERANGE && (value > DBL_MAX || value < -DBL_MAX))
    {
        printAllImpossible();
        return ;
    }

    printChar(value);
    printInt(value);
    // Un double puo' essere troppo grande per un float (es. 1e300).
    if (value > static_cast<double>(FLT_MAX) || value < static_cast<double>(-FLT_MAX))
        std::cout << "float: impossible" << std::endl;
    else
        printFloat(static_cast<float>(value));
    printDouble(value);
}

void notConvert(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else if (literal == "-inf" || literal == "-inff")
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}
