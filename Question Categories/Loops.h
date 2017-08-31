
#ifndef __LOOPS_H__
#define __LOOPS_H__

#include "question.h"
#include "Loops Subclasses/QLoops.h"	//these are the classes for calculating the questions
#include "Loops Subclasses/ForLoops.h"
#include "Loops Subclasses/WhileLoops.h"
#include "Loops Subclasses/DoLoops.h"

//-------------------------------------------------------------------------------------------------------------------
//"outputting questions"
//the classes that compose the ones above and actually use their functions and stuff

//master class that hold common functions and interface
//including general answer making functions
class Loops : public Question
{
public:
	Loops(int loopType) : Question()
	{
		category = loopType;
	};
	
	virtual ~Loops() {};
	
	void Tests();

private:

	int category; //the actual question category
				  //0 - For Loops
				  //1 - While Loops
				  //2 - Do While Loops
	
	//functions that call the question generators
	void TypeOne();
	void TypeTwo();
	void TypeThree();
	void TypeFour();
	
	void SingleLoopCount(QLoops* current, int minIterations, int maxIterations);
	/*==================== void SingleLoopCount(QLoops* current, int minIterations, int maxIterations) ====================
 	DESC:	This function generates a single loop and asks how many iterations it goes through
	PARAM:	QLoops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a dervied class of QLoops
 	POST: 	Question is finished
 	LOC: 	Loops.cpp
 	EX:		
 	=====================================================*/
	
	void NestedLoopCount(QLoops* current, int minIterations, int maxIterations);
	/*==================== void NestedLoopCount(QLoops* current, int minIterations, int maxIterations) ====================
 	DESC:	A function that is very similar to the one above except for nested loops
	PARAM:	QLoops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a derived class of QLoops
 	POST: 	Question is finished 
 	LOC: 	Loops.cpp
 	EX:		
 	=====================================================*/
	
	void SingleLoopPrint(QLoops* current, int minIterations, int maxIterations);
	/*==================== void SingleLoopPrint(QLoops* current, int minIterations, int maxIterations) ====================
 	DESC:	A function that generates a question similar to the two above, except it asks for the output of the loop
			See README for more details
	PARAM:	QLoops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a derived class of QLoops
 	POST: 	Question is finished 
 	LOC: 	Loops.cpp
 	EX:		
 	=====================================================*/
	
	void CheckAndPrintAnswers(const int& tempCorrect, vector<int>& tempWrong);
	/*==================== void CheckAndPrintAnswers(const int& tempCorrect, vector<int>& tempWrong) ====================
 	DESC:	Just a basic function that checks the answers and then prints them, which is used at the end of every question
	PARAM:	const int& tempCorrect - the correct answer
			vector<int>& tempWrong - the wrong answers
 	PRE: 	
 	POST: 	Question is finished and printed
 	LOC: 	Loops.cpp
 	EX:		
 	=====================================================*/
	
	void CheckAndPrintAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong);
	/*==================== void CheckAndPrintAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong) ====================
 	DESC:	An overload of the funciton above
	PARAM:	const vector<int>& tempCorrect - the correct answer
			vector<vector<int>>& tempWrong - the wrong answers
 	PRE: 	
 	POST: 	Question is finished and printed
 	LOC: 	Loops.cpp
 	EX:		
 	=====================================================*/
};

#endif