#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    std::cout << "=== Test 1: Create valid Form and valid Bureaucrat ===" << '\n';
    try {
        Form taxForm("Tax Form", 50, 25);
        std::cout << taxForm << '\n';
        
        Bureaucrat alice("Alice", 30);
        std::cout << alice << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 2: Bureaucrat with sufficient grade signs form successfully ===" << '\n';
    try {
        Form contract("Contract", 100, 50);
        Bureaucrat bob("Bob", 50);
        
        std::cout << "Before signing:\n" << contract << '\n';
        bob.signForm(contract);
        std::cout << "After signing:\n" << contract << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 3: Bureaucrat with insufficient grade tries to sign form ===" << '\n';
    try {
        Form topSecret("Top Secret", 10, 5);
        Bureaucrat charlie("Charlie", 50);
        
        std::cout << "Before signing attempt:\n" << topSecret << '\n';
        charlie.signForm(topSecret);
        std::cout << "After signing:\n" << topSecret << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    return 0;
}