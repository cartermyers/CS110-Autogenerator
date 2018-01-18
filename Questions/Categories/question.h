// ------------------------------------------
// question.h
// Definition of the Question class
// with some implementation of templated functions
//--------------------------------------------


//TODO: MAKE ALL RANGE PARAMETERS (like maxVal, etc.) INCLUSIVE

// Every function must have comments of this style in the header
// (I know it looks dumb but I think it may be useful)

/*====================FUNCTION NAME====================
 DESC: 	description here
 PARAM:	description of each parameter
 PRE: 	any preconditions here
 POST: 	any post conditions (result of function)
 LOC: 	file location of implementation (e.g. question.cpp)
 EX:	example call
 =====================================================*/

#ifndef __QUESTION_H__
#define __QUESTION_H__

#include "../Generators/general.h"

//TODO
//TEMPORARY INCLUDE:
#include "../Generators/Expressions.h"

using namespace std;

//*******************************************************************************************
//							QUESTIONS SUPERCLASS DEFINITIONS
//
//				abstract class that holds all the same attributes for every question
//				eith some procedures that are used comewhat frequently across different classes
//*******************************************************************************************
class Question {
public:

	Question();
	/*==================== Question() ====================
 	DESC: 	Simple constructor for the Question superclass
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	All private members are superficially initialized.
			The size of the wrong array is 4.
 	LOC: 	question.cpp
 	EX:		Question* thing = new Question();
 	=====================================================*/

	Question(int wrongSize);
	/*==================== Question(int wrongSize) ====================
 	DESC: 	Simple constructor for the Question superclass, with explicit
			number of wrong answers.
	PARAM:	int wrongSize - number of wrong answers wanted
 	PRE: 	No preconditions
 	POST: 	All private members are superficially initialized.
			The size of the wrong array is now wrongSize.
 	LOC: 	question.cpp
 	EX:		Question* thing = new Question(2);
 	=====================================================*/

	virtual ~Question() {};
	/*==================== ~Question() ====================
 	DESC: 	Simple destructor for the question class.
			Currently does nothing because no dynamic memory
			is used in the superclass.
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	The instance of Question is deallocated
 	LOC: 	question.h
 	EX:		delete thing; //where thing is a pointer to a question
 	=====================================================*/

	void Generate();
	/*==================== void Generate() ====================
 	DESC: 	Calls a function to generate an answer (one of the
			Type() functions) based on the
			is used in the superclass.
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	The instance of Question is deallocated
 	LOC: 	question.cpp
 	EX:		thing->Generate; //where thing is a pointer to a question
 	=====================================================*/

	void Print(ofstream& out);
	/*==================== void Print(ofstream& out) ====================
 	DESC: 	Takes the datat members of the Question and prints them out
			to the given ofstream (file, cout, etc.) in the proper
			GIFT format.
	PARAM:	ofstream& out - the output stream for the function to print
 	PRE: 	All of the answer data members have been initialized
 	POST: 	The ofstream has a GIFT format question printed out
 	LOC: 	question.cpp
 	EX:		thing->Print(cout); //where thing is a pointer to a question
 	=====================================================*/

	void SetDifficulty(int difficult);
	/*==================== void SetDifficulty(int difficult) ====================
 	DESC: 	A simple setter for the private member difficulty.
	PARAM:	int difficult - the desired value of difficulty
 	PRE: 	difficult is a value between 1-4 (see Generate for reason)
 	POST: 	difficulty has value of difficult
 	LOC: 	question.cpp
 	EX:		thing->SetDifficulty(2); //where thing is a pointer to a question
 	=====================================================*/

	void FinalAnswerCheck();
	/*==================== void FinalAnswerCheck() ====================
 	DESC: 	A check to see if the answers are all unique.
			NOTE: DOESN'T check to see if the answer is correct. That is
			the responsibility of the subclass.
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	All answers are unique or an exception of SameAnswers is thrown
 	LOC: 	question.cpp
 	EX:		thing->FinalAnswerCheck(); //where thing is a pointer to a question
 	=====================================================*/

	virtual void Tests();
	/*==================== void Tests() ====================
 	DESC: 	A function that holds all the tests of the class.
			It should not be expected that everything function is tested
			since it is hard to test functions like Print(). But at the
			very leat, the function used to obtain the answer to the
			question should be tested here. Even if it is a simple swap.

			Side note: There may be other test functions implemented,
			but they must all be called in here.
	PARAM:	No parameters
 	PRE: 	No preconditions
 	POST: 	The class is properly tested (I hope)
 	LOC: 	question.cpp
 	EX:		thing->Question::Tests(); //scope resolution is needed because it is virtual
 	=====================================================*/

protected:
	string prompt;			//the prompt for the question; the actual "asking"
	string correct;			//the correct answer
	vector<string> wrong;	//any wrong answers
	int difficulty; 		//difficulty of question

	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------- NON-TEMPLATED FUNCTIONS ----------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------


	/*

	TODO: AGAIN, MOST OF THESE SHOULDNT BE HERE

	*/

	void CheckUniqueAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong);
	/*==================== void CheckUniqueAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong) ====================
 	DESC:	An overloaded function for this class to check unique arrays
	PARAM:	const vector<int>& tempCorrect - the correct answer
			vector<vector<int>>& tempWrong - the wrong answers
 	PRE: 	tempCorrect.size() == tempWrong[i].size() for i in tempWrong.size()
 	POST: 	All answers in tempWrong are unique and are not equal to tempCorrect
 	LOC: 	question.cpp
 	EX:		CheckUniqueAnswers(tempCorrect, tempWrong);
 	=====================================================*/

	bool IsSame(vector<int> A, vector<int> B);
	/*==================== bool IsSame(vector<int> A, vector<int> B) ====================
 	DESC:	An overloaded function for this class to check if two arrays are the same
	PARAM:	vector<int> A - the first vector
			vector<int> B - the second vector
 	PRE: 	No preconditions
 	POST: 	false if all elements in A are equal to all elements in B (in the proper order) else true
 	LOC: 	question.cpp
 	EX:		IsSame({1, 2}, {1, 2}); //true
 	=====================================================*/

//TODO: DO WE NEED THESE FUNCITONS
	//if so, they probably are only needed in the function above, so they should be moved
	int Factorial(int n);
	//just a quick factorial function that is used in DistinctRearrangements

	int NumOfPermutations(vector<int> original);
	/*==================== int DistinctRearrangements(vector<int> original) ====================
	DESC:	A function that computes the number of unique permutations for a given vector
	PARAM:	vector<int> original - the original vector
	PRE: 	No preconditions
	POST: 	Returns the number of unique permutations for the vector
	LOC: 	question.cpp
	EX:		NumOfPermutations({1, 2, 3}) == 6;
			NumOfPermutations({1, 1, 1}) == 1;
	=====================================================*/

	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------- TEMPLATED FUNCTIONS --------------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------

	template <typename T, typename U>
	void CheckUniqueAnswers(const T& tempCorrect, vector<U>& tempWrong, int precision = 2);
	/*==================== void CheckUniqueAnswers(const T& tempCorrect, vector<U>& tempWrong, int precision = 2) ====================
	DESC:	Given the correct answer and some wrong answers, determine if there are any that are the same and changes them if they are
	PARAM:	const T& tempCorrect - the correct answer
	vector<U>& tempWrong - the wrong answers
	int precision - the number of decimal places to compare up to (default is 2)
	PRE: 	No preconditions
	POST: 	All answers in tempWrong are unique and are not equal to tempCorrect
	LOC: 	question.h
	EX:		CheckUniqueAnswers<int, float>(tempCorrect, tempWrong);
	=====================================================*/

	//These functions are purely virtual,
	//they are basically just wrapper functions to call different difficulties of questions
	virtual void TypeOne() = 0;
	virtual void TypeTwo() = 0;
	virtual void TypeThree() = 0;
	virtual void TypeFour() = 0;
};

//a basic exception class:
class SameAnswers {
public:
	vector<string> answers;
	SameAnswers(const string& right, const vector<string>& wrongs)
	{
		answers.push_back(right);
		for (size_t i = 0; i < wrongs.size(); i++)
		{
			answers.push_back(wrongs[i]);
		}
	};
};

//*******************************************************************************************
//							QUESTIONS SUPERCLASS TEMPLATE DEFINITIONS
//
//				since i use templates with some functions, and templates are
//				ridiculous on trying to implement separately,
//				i just decided to add them here
//*******************************************************************************************

//check if the given correct answer and any wrong answers are the same
//and if so, changes the appropriate wrong answer
template <typename T, typename U>
void Question::CheckUniqueAnswers(const T& tempCorrect,
								  vector<U>& tempWrong,
								  int precision)
{
	size_t n = tempWrong.size();
	bool unique = true; 	//this is a flag that goes through and checks the element again if we had to change it

	for (size_t i = 0; i < n; i++)
	{
		do
		{
			unique = true;

			if (Operation<bool, U, T>(eq, tempWrong[i], tempCorrect, precision))
			{
				tempWrong[i] = Operation<U>(GenerateRand<Symbols>(add, sub), tempWrong[i], GenerateRand<U>(1, 3, 2));
				//don't need to change the unique flag here because it'll be checking the others in the next for loop anyway
			}

			//check against EVERY other element in the array
			for (size_t j = i + 1; j < (n + i); j++)
			{
				if (Operation<U, U>(eq, tempWrong[i], tempWrong[j % n], precision))
				{
					tempWrong[i] = Operation<U>(GenerateRand<Symbols>(add, sub), tempWrong[i], GenerateRand<U>(1, 3, 2));
					unique = false;	//now that we've changed this element we need to recheck it
					break;			//so don't bother comparing the new value because we'll be rechecking against all values again
				}
			}
		} while (!unique);
	}
}

#endif
