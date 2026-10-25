#include "Bureaucrat.hpp"

int main()
{
	std::cout << "\n\n=== Valid grades and operators ===" << std::endl;
	Bureaucrat middle("Alice", 75);
	Bureaucrat highest("Top", 1);
	Bureaucrat lowest("Bottom", 150);
	std::cout << "Getter check: " << middle.getName()
		<< " has grade " << middle.getGrade() << std::endl;
	std::cout << middle << highest << lowest;

	std::cout << "\n\n=== Increment and decrement ===" << std::endl;
	middle.incrementGrade();
	std::cout << middle;
	middle.decrementGrade();
	std::cout << middle;

	std::cout << "\n\n=== Invalid constructor grades ===" << std::endl;
	try
	{
		Bureaucrat tooHigh("Too high", 0);
		std::cout << tooHigh;
	}
	catch (const std::exception &e)
	{
		std::cout << "Constructor rejected grade 0: " << e.what() << std::endl;
	}
	try
	{
		Bureaucrat tooLow("Too low", 151);
		std::cout << tooLow;
	}
	catch (const std::exception &e)
	{
		std::cout << "Constructor rejected grade 151: " << e.what() << std::endl;
	}

	std::cout << "\n\n=== Boundary changes ===" << std::endl;
	try
	{
		highest.incrementGrade();
	}
	catch (const std::exception &e)
	{
		std::cout << "Cannot increment grade 1: " << e.what() << std::endl;
	}
	std::cout << "Top after failed increment: " << highest;
	try
	{
		lowest.decrementGrade();
	}
	catch (const std::exception &e)
	{
		std::cout << "Cannot decrement grade 150: " << e.what() << std::endl;
	}
	std::cout << "Bottom after failed decrement: " << lowest;

	std::cout << "\n\n=== Copy construction and assignment ===" << std::endl;
	Bureaucrat copy(middle);
	Bureaucrat assigned("Bob", 100);
	assigned = middle;
	std::cout << "Copy: " << copy;
	std::cout << "Assigned (name stays Bob): " << assigned;

	return 0;
}
