
#ifndef __LOOPS_H__
#define __LOOPS_H__

#include "../general.h"

//interface for the actual question classes:
class Loops
{
public:

	//TODO: make a random generation constructor

	Loops(int minIters = 2, int maxIters = 5, bool improperLoops = false);
	/*==================== Loops() ====================
 	DESC:	A basic constructor for the class. Doesn't really do anything at this point,
			but InitializeLoop() may be called to properly set the data members
	PARAM:	None
 	PRE: 	None
 	POST: 	All data members are set to -1.
 	LOC: 	Loops.cpp
 	EX:
 	=====================================================*/

	//TODO: change to copy?
	Loops(Loops* old);
	//a constructor for deep copies
	
	Loops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
		start(begin), compSymb(symbol), stop(end), incSymb(incSymb), increment(inc) {};
	//an explicit constructor (mostly used for testing)

	virtual ~Loops() {};

	virtual void Tests();

	void SetLoopParameters(bool improperLoops, int minIters = -1, int maxIters = -1);

	void InitializeLoop(Symbols minCompSymb = lt, Symbols maxCompSymb = lt, Symbols minIncSymb = add, Symbols maxIncSymb = add);
	/*==================== void InitializeLoop(bool setSymb = true) ====================
 	DESC:	This function initializes the for loop variables (randomly) dependent on the private members
	PARAM:	bool setSymb - an option to set the symb data member
 	PRE: 	If setSymb == false, then the symb is already set
			NOTE: it is impossible to set the symb outside a member function at current (just add a setter function)
			But I am leaving this implementation if I want to simplify things in the future.
			For example, previous questions only used the '<' comparison operator. It would be nice
			to have that option available in the future.
 	POST: 	All data members are initialized to a valid (meaning it will terminate) for loop
 	LOC: 	
 	EX:
 	=====================================================*/

	int ComputeLoop();
	/*==================== int ComputeLoop() ====================
 	DESC:	Counts how many iterations the loop takes, then changes the members 
			if the number of iterations does not fall between min and max inclusive
	PARAM:	int min - the minimum amount of iterations
			int max - the maximum amount of iterations
 	PRE: 	symb, start, end, increment, and incSymb are initalized (should be handled in InitializeLoop())
			min < max
 	POST: 	Some private members (stop, incSymb) may be changed to suit the loop better, depending on the class
			The number of loop executions is returned.
 	LOC: 	
 	EX:
 	=====================================================*/

	vector<int> ShowLoop();
	/*==================== vector<int> ShowLoop(int min, int max) ====================
 	DESC:	Changes the data members to have the number of iterations between min and max (inclusive)
			Then it returns a vector that is the value of the iterator at every step
	PARAM:	int min - the minimum amount of iterations
			int max - the maximum amount of iterations
 	PRE: 	symb, start, end, increment, and incSymb are initalized (should be handled in InitializeLoop())
			min < max
 	POST: 	Some private members (stop, incSymb) may be changed to suit the loop better
			The values of the iterator are returned
 	LOC: 	Loops.cpp
 	EX:
 	=====================================================*/

	//Printer Functions:
	virtual string Print(string id, string body) = 0;
	/*==================== string PrintLoop(Loops* current, string id, string printerId) ====================
 	DESC:	Prints a single loop in the proper format.
	PARAM:	string id - the id of the counter
			string body - the body of the loop (see README for question details)
 	PRE: 	All data members are intialized
 	POST: 	Returns a string of the loop
 	LOC: 	LoopsPrinters.cpp
 	EX:
 	=====================================================*/

	//simple getter functions
	int GetStart() { return start; };

	Symbols GetCompSymb() { return compSymb; };

	int GetStop() { return stop; };

	Symbols GetIncSymb() { return incSymb; };

	int GetIncrement() { return increment; };

	bool GetAllowImproperLoops() { return allowImproperLoops; };

protected:

 	virtual int CountIterations();
	/*==================== int CountIterations(int begin, int symbol, int end, int inc) ====================
 	DESC:	This function counts the number of iterations in a *for* loop given the parameters.
	PARAM:	int begin - the starting value
			Symbols symbol - the index of the comparison operator
			int end - the terminating value to compare against
			int inc - the amount to increment by
 	PRE: 	No preconditions
 	POST: 	Returns the number of times a loop executes
 	LOC: 	Loops.cpp
 	EX:
 	=====================================================*/

	virtual vector<int> ShowIterations();
	/*==================== vector<int> ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb) ====================
 	DESC:	This function returns a vector of the values of the "counter" or iterator at each iteration of the loop
	PARAM:	int begin - the starting value
			Symbols symbol - the index of the comparison operator
			int end - the terminating value to compare against
			int inc - the amount to increment by
 	PRE: 	No preconditions
 	POST: 	Returns a vector of the values of the counter at each iteration
 	LOC: 	Loops.cpp
 	EX:
 	=====================================================*/

	//the data members:
	int start;			//the starting value
	Symbols compSymb; 	//the index of the comparison operator (i.e. <, <=, etc.)
	int stop;			//the terminating value
	Symbols incSymb;	//the index of the increment (either + or - for now)
	int increment;		//the value to change by

	//meta data members:
	int minIterations;			//the minimum number of iterations for a loop
	int maxIterations;			//the maximum number of iterations
	bool allowImproperLoops;	//an option to create loops that "never" terminate
};

#endif
