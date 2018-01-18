// A program to perform tests on each question category
// NOTE: All tests should be written in the function Tests() for each class
// as it can test private functions that are not callable in this scope.
// This program is mainly an environment to run the Tests() functions

#include <iostream>
#include "../Questions/Categories/question.h"
#include "../Questions/Categories/all_questions.h"

int main()
{
	try
	{
		Question* tester = new QArrays();

		//first, test the superclass:
		tester->Question::Tests();

		//then all the subclasses:

		//Arrays:
		tester->Tests();
		delete tester;

		//for loops
		tester = new QLoops(0, 0);	//these numbers don't matter for initialization, as all tests for loops are at QLoops::Tests()
		tester->Tests();
		delete tester;

		//expressions
		tester = new QExpressions();
		tester->Tests();
		delete tester;

		//functions
		tester = new QFunctions();
		tester->Tests();
		delete tester;

		//switch cases
		tester = new QSwitchCases();
		tester->Tests();
		delete tester;

		//identifiers
		tester = new QIdentifiers();
		tester->Tests();
		delete tester;

		//conditionals
		tester = new QConditionals();
		tester->Tests();
		delete tester;

		tester = NULL;

		cout << "All tests have passed.\n";
	}
	catch (exception &e)
	{
		cout << "An error was found with the statement: " << e.what() << endl;
	}

	system("pause");
	return 0;
}
