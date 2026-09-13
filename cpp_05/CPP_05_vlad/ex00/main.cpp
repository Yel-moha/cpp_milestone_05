#include "Bureaucrat.hpp"

int main()
{
    std::cout << "=== Test 1: Constructor valid (grade 75) ===" << '\n';
    try {
        Bureaucrat alice("Alice", 75);
        std::cout << alice << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 2: Constructor grade prea mare (0) ===" << '\n';
    try {
        Bureaucrat bob("Bob", 0);
        std::cout << bob << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 3: Constructor grade prea mic (151) ===" << '\n';
    try {
        Bureaucrat charlie("Charlie", 151);
        std::cout << charlie << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 4: incrementGrade valid (3 -> 2) ===" << '\n';
    try {
        Bureaucrat dave("Dave", 3);
        std::cout << "Înainte: " << dave << '\n';
        dave.incrementGrade();
        std::cout << "După increment: " << dave << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 5: incrementGrade cu grade 1 (1 -> 0 = excepție) ===" << '\n';
    try {
        Bureaucrat eve("Eve", 1);
        std::cout << "Înainte: " << eve << '\n';
        eve.incrementGrade();
        std::cout << "După increment: " << eve << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 6: decrementGrade valid (148 -> 149) ===" << '\n';
    try {
        Bureaucrat frank("Frank", 148);
        std::cout << "Înainte: " << frank << '\n';
        frank.decrementGrade();
        std::cout << "După decrement: " << frank << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 7: decrementGrade cu grade 150 (150 -> 151 = excepție) ===" << '\n';
    try {
        Bureaucrat grace("Grace", 150);
        std::cout << "Înainte: " << grace << '\n';
        grace.decrementGrade();
        std::cout << "După decrement: " << grace << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 8: Copy constructor ===" << '\n';
    try {
        Bureaucrat original("Original", 42);
        Bureaucrat copy(original);
        std::cout << "Original: " << original << '\n';
        std::cout << "Copy: " << copy << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 9: Assignment operator ===" << '\n';
    try {
        Bureaucrat john("John", 100);
        Bureaucrat jane("Jane", 50);
        std::cout << "Înainte assignment:" << '\n';
        std::cout << "John: " << john << '\n';
        std::cout << "Jane: " << jane << '\n';
        
        john = jane;
        std::cout << "După john = jane:" << '\n';
        std::cout << "John: " << john << '\n';
        std::cout << "Jane: " << jane << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Test 10: Multiple increment/decrement ===" << '\n';
    try {
        Bureaucrat kim("Kim", 5);
        std::cout << "Start: " << kim << '\n';
        kim.incrementGrade();
        std::cout << "După increment: " << kim << '\n';
        kim.incrementGrade();
        std::cout << "După al doilea increment: " << kim << '\n';
        kim.decrementGrade();
        std::cout << "După decrement: " << kim << '\n';
    }
    catch (std::exception& e) {
        std::cout << RED << "Error: " << e.what() << '\n' << RESET;
    }

    std::cout << "\n=== Toate testele finalizate ===" << '\n';
    return 0;
}