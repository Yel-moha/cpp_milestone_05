#include "B.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib> //std::rand, std::srand
#include <ctime>   //std::time


Base * generate(void);
void identify(Base* p);
void identify (Base& p);

Base * generate(void)
{
    int r = std::rand() % 3;
    switch (r)
    {
        case 0:
            std::cout << "A: Created " << std::endl;
            return new A;
        case 1:
            std::cout << "B: Created " << std::endl;
            return new B;
        case 2:
            std::cout << "C: Created " << std::endl;
            return new C;
        default:
            return nullptr;
    }

}

void identify(Base* p)
{
    
}




int main(void)
{
    std::srand(std::time(NULL)); // per il seme di partenza


    return (0);
}
