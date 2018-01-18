
#ifndef __QLOOPS_H__
#define __QLOOPS_H__

#include "question.h"
#include "../Generators/Loops/Loops.h"	//these are the classes for calculating the questions
#include "../Generators/Loops/ForLoops.h"
#include "../Generators/Loops/WhileLoops.h"
#include "../Generators/Loops/DoLoops.h"

//-------------------------------------------------------------------------------------------------------------------
//"outputting questions"
//the classes that compose the ones above and actually use their functions and stuff

//master class that hold common functions and interface
//including general answer making functions
class QLoops : public Question
{
public:
	QLoops(int loop, int questionType);
	
	virtual ~QLoops();
	
	void Tests();

private:

	Loops* currentLoop;	//the actual loop type

	int loopType;	//0 - For Loops
					//1 - While Loops
					//2 - Do While Loops

	int type;		//the type of question
					// 0 - Counting
					// 1 - Printing
	
	void TypeOne();
	void TypeTwo();
	void TypeThree();
	void TypeFour();


	void SingleLoopCount();
	/*==================== void SingleLoopCount(Loops* current, int minIterations, int maxIterations) ====================
 	DESC:	This function generates a single loop and asks how many iterations it goes through
	PARAM:	Loops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a dervied class of Loops
 	POST: 	Question is finished
 	LOC: 	QLoops.cpp
 	EX:		
 	=====================================================*/
	
	void NestedLoopCount(Loops* innerLoop);
	/*==================== void NestedLoopCount(Loops* current, int minIterations, int maxIterations) ====================
 	DESC:	A function that is very similar to the one above except for nested loops
	PARAM:	Loops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a derived class of Loops
 	POST: 	Question is finished 
 	LOC: 	QLoops.cpp
 	EX:		
 	=====================================================*/
	
	void SingleLoopPrint();
	/*==================== void SingleLoopPrint(Loops* current, int minIterations, int maxIterations) ====================
 	DESC:	A function that generates a question similar to the two above, except it asks for the output of the loop
			See README for more details
	PARAM:	Loops* current - the type of loop used to calculate and print
			int minIterations - the minimum amount of iterations for the loop
			int maxIterations - the maximum amount of iterations for the loop
 	PRE: 	current is assigned a derived class of Loops
 	POST: 	Question is finished 
 	LOC: 	QLoops.cpp
 	EX:		
 	=====================================================*/
	
	void CheckAndPrintAnswers(const int& tempCorrect, vector<int>& tempWrong);
	/*==================== void CheckAndPrintAnswers(const int& tempCorrect, vector<int>& tempWrong) ====================
 	DESC:	Just a basic function that checks the answers and then prints them, which is used at the end of every question
	PARAM:	const int& tempCorrect - the correct answer
			vector<int>& tempWrong - the wrong answers
 	PRE: 	
 	POST: 	Question is finished and printed
 	LOC: 	QLoops.cpp
 	EX:		
 	=====================================================*/
	
	void CheckAndPrintAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong);
	/*==================== void CheckAndPrintAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong) ====================
 	DESC:	An overload of the funciton above
	PARAM:	const vector<int>& tempCorrect - the correct answer
			vector<vector<int>>& tempWrong - the wrong answers
 	PRE: 	
 	POST: 	Question is finished and printed
 	LOC: 	QLoops.cpp
 	EX:		
 	=====================================================*/
};

#endif