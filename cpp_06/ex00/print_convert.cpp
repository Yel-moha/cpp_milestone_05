#include "ScalarConverter.hpp"
// DA CORREGGERE (nome): "covertTo..." ha un typo, manca la 'n' -> "convertTo...".
// Non e' un errore di compilazione, ma in valutazione si nota. Rinominalo qui,
// nell'.hpp e nello switch di ScalarConverter.cpp.
void covertToChar(const std::string& literal)
{
    char c = literal.length() == 1 ? literal[0] : literal[1];
    int value = static_cast<unsigned char>(c);

    std::cout << "char: ";
    // DA CORREGGERE (logica): int, float e double vengono stampati SOLO dentro
    // il ramo "isprint". Se il char non e' stampabile (o > 127) il programma
    // stampa solo "char: ..." e si ferma: mancano 3 righe di output.
    // COME: stampa qui sotto solo la riga del char (if/else if/else), poi FUORI
    // dall'if stampa sempre int, float e double.
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
    // DA CORREGGERE (overflow): atol non segnala errori. Con un input enorme
    // (es. 999999999999999999999) va in overflow del long e restituisce un
    // valore sbagliato (LONG_MAX o spazzatura), quindi float/double stampano
    // numeri falsi.
    // COME: usa std::strtol e controlla errno (#include <cerrno>):
    //     errno = 0;
    //     long value = std::strtol(literal.c_str(), NULL, 10);
    //     if (errno == ERANGE) -> overflow
    // Il subject dice anche: prima converti la stringa nel suo tipo reale (int),
    // poi fai il cast esplicito agli altri tre tipi.
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
    // DA CORREGGERE (controllo inutile): un long non puo' mai superare FLT_MAX
    // (circa 3.4e38), quindi questo if e' sempre falso. Puoi toglierlo.
    if(value < -FLT_MAX || value > FLT_MAX)
        std::cout << "impossible" << std::endl;
    else
        // DA CORREGGERE (formato): aggiungere ".0f" a mano funziona solo per
        // numeri piccoli. Con valori grandi cout passa alla notazione
        // scientifica e stampa "2.14748e+09.0f", che e' sbagliato.
        // Prova: ./convert 2147483648 oppure ./convert 100000000
        // COME: usa std::fixed e std::setprecision(1) (#include <iomanip>):
        //     std::cout << std::fixed << std::setprecision(1) << f << "f";
        // oppure scrivi il numero in un std::ostringstream e aggiungi ".0" solo
        // se nella stringa non ci sono gia' '.' o 'e'.
        std::cout << static_cast<float>(value) << ".0f" << std::endl;
    // DA CORREGGERE (formato): stesso problema di sopra, "2.14748e+09.0".
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void covertToFloat(const std::string& literal)
{

    // DA CORREGGERE (tipo): atof restituisce un DOUBLE, non un float. Il subject
    // chiede di convertire la stringa nel suo tipo reale (float) e poi fare il
    // cast agli altri tipi. Cosi' stai lavorando in double e la precisione del
    // float non si vede (es. 16777217.0f in float vale 16777216).
    // COME: float value = std::strtof(literal.c_str(), NULL);
    // con errno == ERANGE per l'overflow (es. un numero oltre 3.4e38 con la 'f').
    double value = std::atof(literal.c_str());
    // DA CORREGGERE (tol): static_cast<long>(value) con un valore fuori dal range
    // del long e' comportamento indefinito. In piu' la tolleranza serve solo a
    // decidere se stampare ".0": con il formato std::fixed / ostringstream
    // (vedi covertToInt) non ti serve piu' e puoi toglierla.
    bool tol = std::fabs(value - static_cast<long>(value)) < 0.0000000000001;
    std::cout << "char: ";
    if (value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    else if (std::isprint(static_cast<unsigned char>(value)))
        std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;

    std::cout << "int: ";
    // DA CORREGGERE (range): static_cast<float>(INT_MAX) vale 2147483648 (il
    // float non rappresenta 2147483647), quindi 2147483648.0f passa il
    // controllo e static_cast<int> va in overflow: comportamento indefinito.
    // COME: confronta in double: static_cast<double>(INT_MAX).
    if (value < static_cast<float>(INT_MIN) || value > static_cast<float>(INT_MAX))
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(value) << std::endl;

    std::cout << "float: ";
    if (value < -FLT_MAX || value > FLT_MAX)
        std::cout << "impossible" << std::endl;
    else
    {
        // DA CORREGGERE (formato): il subject vuole "42.0f", quindi la logica e'
        // giusta, ma con numeri grandi (es. 100000000.0f) cout stampa "1e+08" e
        // ottieni "1e+08.0f". Stessa soluzione di covertToInt (fixed oppure
        // ostringstream + controllo di '.' ed 'e').
        std::cout << value ;
        if(tol)
            std::cout << ".0f" <<std::endl;
        else
            std::cout << "f" << std::endl;
    }

    // DA CORREGGERE (formato): stesso problema, "1e+08.0".
    std::cout << "double: " << static_cast<double>(value) << (tol ? ".0" : "") << std::endl;
}

void covertToDouble(const std::string& literal)
{
    // FIXME: valutare parser piu robusto rispetto ad atof.
    // DA CORREGGERE (overflow): atof non segnala errori. Usa std::strtod e
    // controlla errno == ERANGE per sapere se il numero supera DBL_MAX.
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
        // DA CORREGGERE (formato): con ./convert 42.0 stampa "42f" invece di
        // "42.0f", perche' cout non stampa i decimali a zero.
        // COME: stessa soluzione di covertToInt (fixed oppure ostringstream e
        // aggiungi ".0" se non c'e' il punto).
        std::cout << static_cast<float>(value) << "f" << std::endl;

    std::cout << "double: ";
    // FIXME: controllo ridondante sul range double; chiarire gestione esplicita di inf/nan.
    // DA CORREGGERE (controllo inutile): un double non puo' essere fuori da
    // [-DBL_MAX, DBL_MAX] a parte inf. inf/nan arrivano gia' a notConvert, e
    // l'overflow va gestito subito dopo strtod con errno. Questo if si toglie.
    if (value < -DBL_MAX || value > DBL_MAX)
        std::cout << "impossible" << std::endl;
    else
        // DA CORREGGERE (formato): con ./convert 42.0 stampa "42" invece di
        // "42.0". Stessa soluzione di sopra.
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
        // DA CORREGGERE (typo output): "char : " ha uno spazio prima dei due
        // punti, deve essere "char: " come nelle altre righe.
        std::cout << "char : impossible" <<std::endl;
        std::cout << "int: impossible" <<std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else if(literal == "-inf" || literal == "-inff")
    {
        // DA CORREGGERE (typo output): "char : " e "int : " hanno uno spazio di
        // troppo. Devono essere "char: " e "int: ".
        std::cout << "char : impossible" <<std::endl;
        std::cout << "int : impossible" <<std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
    // CONSIGLIO: le prime due righe sono uguali in tutti e tre i casi. Puoi
    // stamparle una volta sola prima degli if.
}