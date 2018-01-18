#ifndef __QSWITCHCASES_H__
#define __QSWITCHCASES_H__

#include "question.h"

class QSwitchCases : public Question {
public:
	QSwitchCases();
	/*==================== QSwitchCases() ====================
 	DESC:	Default constructor
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	All data members are initialized, some randomly
 	LOC: 	QSwitchCases.cpp
 	EX:		
 	=====================================================*/

	QSwitchCases(int swit, vector<int> comparisons, vector<int> results, vector<bool> breakers, bool wantDefault);
	/*==================== QSwitchCases(int swit, vector<int> comparisons, vector<int> results, vector<bool> breakers, bool wantDefault) ====================
 	DESC:	An explicit constructor for nearly all members; mostly used for testing
	PARAM:	int swit - the main value to be compared
			vector<int> comparisons - the values of the cases
			vector<int> results - the results of the cases
			vector<bool> breakers - if the cases have a break statement
			bool wantDefault - if the representation has a default value
 	PRE: 	All vectors have the proper size relational to one another (taking into account default, etc.)
 	POST: 	All data members are initialized to the parameters
 	LOC: 	QSwitchCases.cpp
 	EX:		
 	=====================================================*/
	
	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC: EvalSwitchCase
	LOC: Functions.cpp
	=====================================================*/

private:

	//Properly add a switch case to the prompt member given all the QSwitchCases members
	void PrintSwitchCase();
	/*==================== void PrintSwitchCase() ====================
 	DESC:	Outputs a switch case statement to the prompt given the data members
	PARAM:	No parameters
 	PRE: 	All the data members are properly initialized
 	POST: 	A switch case structure is added to the prompt
 	LOC: 	QSwitchCases.cpp
 	EX:		
 	=====================================================*/

	int EvalSwitchCase(vector<int>& wrongAnswers);
	/*==================== int EvalSwitchCase(vector<int>& wrongAnswers) ====================
 	DESC:	Evaluate a switch case given the data members, and generate wrong answers in the process
	PARAM:	vector<int>& wrongAnswers - a vector to be modified with wrong answers
 	PRE: 	All the data members are properly initialized
 	POST: 	The correct answer is returned, and wrongAnswers is changed
 	LOC: 	QSwitchCases.cpp
 	EX:		
 	=====================================================*/

	void Finish();
	/*==================== void Finish() ====================
 	DESC:	a basic function that handles the printing and computing of the question after all the members have been determined
	PARAM:	No parameters
 	PRE: 	All the data members are properly initialized (handled in constructor)
 	POST: 	The question is printed and the answers are assigned
 	LOC: 	QSwitchCases.cpp
 	EX:		
 	=====================================================*/

	//members:
	int switcher;				//the main value to be compared
	string switcher_id;			//the id
	vector<int> cases;			//the values of comparison
	vector<int> caseResults;	//the results of the comparisons
	vector<bool> breaks;		//any break statements
	bool hasDefault;			//if the structure has a default case
	int size;					//the total number of cases

	void TypeOne();
	/*==================== void TypeOne() ====================
 	DESC: Doesn't change any data members, uses all random members from constructor
	E.g.: 
 	=====================================================*/
	
	void TypeTwo();
	/*==================== void TypeTwo() ====================
 	DESC: A standard switch case with all breaks and a default
	E.g.: 
 	=====================================================*/
	
	void TypeThree();
	/*==================== void TypeThree() ====================
 	DESC: This switch case has no breaks, but always a default
	E.g.: 
 	=====================================================*/
	
	void TypeFour();
	/*==================== void TypeFour() ====================
 	DESC: This has no breaks and no defualt
	E.g.: 
 	=====================================================*/
};

#endif