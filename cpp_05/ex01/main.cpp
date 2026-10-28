#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "=== Forms and required grades ===" << std::endl;
	Form taxForm("Tax form", 50, 25);
	Form easyForm("Easy form", 100, 75);
	std::cout << taxForm << std::endl;
	std::cout << easyForm << std::endl;

	std::cout << "\n=== Signing success and failure ===" << std::endl;
	Bureaucrat senior("Senior", 20);
	Bureaucrat junior("Junior", 80);
	junior.signForm(taxForm);
	senior.signForm(taxForm);
	junior.signForm(easyForm);
	std::cout << "Tax form signed: " << std::boolalpha << taxForm.getIsSigned() << std::endl;
	std::cout << "Easy form signed: " << easyForm.getIsSigned() << std::noboolalpha << std::endl;

	std::cout << "\n=== Direct beSigned call ===" << std::endl;
	try
	{
		easyForm.beSigned(senior);
		std::cout << "Senior signed Easy form directly" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Direct signing failed: " << e.what() << std::endl;
	}

	std::cout << "\n=== Invalid form grades ===" << std::endl;
	try
	{
		Form invalidHigh("Invalid high", 0, 10);
		std::cout << invalidHigh << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Rejected grade 0: " << e.what() << std::endl;
	}
	try
	{
		Form invalidLow("Invalid low", 10, 151);
		std::cout << invalidLow << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Rejected grade 151: " << e.what() << std::endl;
	}

	std::cout << "\n=== Copy and assignment ===" << std::endl;
	Form copied(taxForm);
	Form assigned("Assigned form", 120, 100);
	assigned = taxForm;
	std::cout << "Copy: " << copied << std::endl;
	std::cout << "Assignment keeps destination name and grades: "
		<< assigned << std::endl;

	return 0;
}
