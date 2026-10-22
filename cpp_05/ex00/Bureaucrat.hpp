#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>

class Bureaucrat {
	private:
		const std::string name;
		int grade; // A grade that ranges from 1
		// (highest possible grade) to 150 (lowest possible grade).

	public:
		Bureaucrat();
        Bureaucrat(const std::string name);
        Bureaucrat(int grade);
        Bureaucrat(const std::string name, int grade);
        Bureaucrat(const Bureaucrat &other);
        Bureaucrat &operator=(const Bureaucrat &other);

        
		std::string getName() const;
		int getGrade() const;


		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "grade is too high";
                }
		};

		class GradeTooLowException
        {
            public:
                virtual const char *what() const throw()
                {
                    return "grade is too low";
                }
		};
        ~Bureaucrat();
};

#endif

/*

Secondo il subject, le eccezioni rappresentano condizioni invalide: chi rileva l’errore fa throw; chi avvia l’operazione fa try/catch e stampa/gestisce il motivo.
La regola chiave è che il voto numericamente più basso è più alto come autorità:
Situazione	Eccezione
grade < 1	GradeTooHighException
grade > 150	GradeTooLowException
Bureaucrat senza autorità per firmare/eseguire (grade > requiredGrade)	GradeTooLowException
Tentativo di eseguire un form non firmato	eccezione dedicata, tipicamente FormNotSignedException


In ex00, Bureaucrat deve avere eccezioni annidate e derivarle da std::exception, altrimenti questo catch richiesto dal subject non funzionerebbe:
catch (std::exception &e)
{
    std::cout << e.what() << std::endl;
}
Schema C++98:
class GradeTooHighException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "grade is too high";
    }
};
Nel costruttore controlli subito il grade. In incrementGrade() e decrementGrade() controlli prima di modificare:
if (_grade == 1)
    throw GradeTooHighException();
--_grade;
if (_grade == 150)
    throw GradeTooLowException();
++_grade;
In ex01, Form valida entrambi i grade nel costruttore. beSigned() deve lanciare Form::GradeTooLowException se il bureaucrat non ha sufficiente autorità:
if (bureaucrat.getGrade() > _gradeToSign)
    throw GradeTooLowException();
_isSigned = true;
In ex02, è più pulito mettere i controlli una sola volta in AForm::execute():
1. se non è firmato → throw FormNotSignedException();
2. se l’esecutore ha grade insufficiente → throw GradeTooLowException();
3. altrimenti chiama una funzione virtuale delle classi concrete per l’azione vera (_executeAction()).
Bureaucrat::signForm() e executeForm() non dovrebbero duplicare queste verifiche: chiamano beSigned()/execute() dentro un try, catturano std::exception, poi stampano successo o l’errore.
In ex03, per un nome form sconosciuto il subject chiede solo un messaggio d’errore esplicito: non impone un’eccezione. Puoi stampare l’errore e restituire NULL.


7:48 PM








cosa chiede il subject riguardo alla forma canonica e ai costruttori 







7:59 PM






Worked for 19s



Il subject impone che, dal Module 02 al 09, ogni classe segua la Orthodox Canonical Form, salvo indicazione contraria.
Quindi per Bureaucrat, Form/AForm, i form concreti e Intern devi prevedere:
ClassName();                         // costruttore di default
ClassName(const ClassName &other);   // copy constructor
ClassName &operator=(const ClassName &other); // copy assignment
~ClassName();                        // distruttore
Le sole eccezioni sono le classi di eccezione (GradeTooHighException, ecc.): il subject dice esplicitamente che non devono essere in forma canonica.
Per i costruttori specifici richiesti:
- Bureaucrat deve poter essere creato con nome e grade, validando subito 1..150.
- Form/AForm devono validare al costruttore i grade necessari per firmare ed eseguire.
- Ogni form concreto in ex02 “takes only one parameter”: il suo target.
- Intern non ha attributi particolari, ma resta comunque una classe in forma canonica.
Poiché name e molti grade sono const, vanno inizializzati con una initializer list:
Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : _name(name), _grade(grade)
{
    if (_grade < 1)
        throw GradeTooHighException();
    if (_grade > 150)
        throw GradeTooLowException();
}
Non puoi assegnare _name nel corpo del costruttore, perché è const.
Con l’operatore =, un membro const non può essere copiato nuovamente. Per Bureaucrat, normalmente copi solo il grade:
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if (this != &other)
        _grade = other._grade;
    return *this;
}
Il nome dell’oggetto a sinistra resta invariato.


7:59 PM

























Approve for me

Select model5.6 TerraMediumNoneMinimalLightMediumHighExtra HighMaxUltraPersistent











Work locallyLocal

*/