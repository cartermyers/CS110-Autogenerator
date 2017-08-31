
#ifndef __QLOOPS_H__
#define __QLOOPS_H__

#include "../question.h"

//interface for the actual question classes:
class QLoops
{
public:

	QLoops();
	/*==================== QLoops() ====================
 	DESC:	A basic constructor for the class. Doesn't really do anything at this point,
			but InitializeLoop() may be called to properly set the data members
	PARAM:	None
 	PRE: 	None
 	POST: 	All data members are set to -1.
 	LOC: 	QLoops.cpp
 	EX:
 	=====================================================*/

	QLoops(QLoops* old);
	//a constructor for deep copies
	
	QLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
		start(begin), symb(symbol), stop(end), incSymb(incSymb), increment(inc) {};
	//an explicit constructor (mostly used for testing)

	virtual ~QLoops() {};

	virtual void Tests() = 0;

	virtual void InitializeLoop(bool setSymb = true) = 0;
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

	virtual int ComputeLoop(int min = 2, int max = 8) = 0;
	/*==================== int ComputeLoop() ====================
 	DESC:	Counts how many iterations the loop takes, then changes the members (in some classes)
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

	vector<int> ShowLoop(int min, int max);
	/*==================== vector<int> ShowLoop(int min, int max) ====================
 	DESC:	Changes the data members to have the number of iterations between min and max (inclusive)
			Then it returns a vector that is the value of the iterator at every step
	PARAM:	int min - the minimum amount of iterations
			int max - the maximum amount of iterations
 	PRE: 	symb, start, end, increment, and incSymb are initalized (should be handled in InitializeLoop())
			min < max
 	POST: 	Some private members (stop, incSymb) may be changed to suit the loop better
			The values of the iterator are returned
 	LOC: 	QLoops.cpp
 	EX:
 	=====================================================*/

	//Printer Functions:
	virtual string PrintLoop(QLoops* current, string id, string printerId) = 0;
	/*==================== string PrintLoop(QLoops* current, string id, string printerId) ====================
 	DESC:	Prints a single loop in the proper format.
	PARAM:	QLoops* current - the type of loop, with the data members, to be printed
			string id - the id of the counter
			string printerId - the id of the print statement inside the loop (see README for question details)
 	PRE: 	All data members are intialized
 	POST: 	Returns a string of the loop
 	LOC: 	LoopsPrinters.cpp
 	EX:
 	=====================================================*/

	virtual string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId) = 0;
	/*==================== string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId) ====================
 	DESC:	Does the same as the function above but with a nested loop
	PARAM:	QLoops* outer - The first loop, as well as the type of loop, with the data members, to be printed
			string outerId - the id of the first counter
			QLoops* inner - The second loop, as well as the type of loop, with the data members, to be printed
			string innerId - the id of the second counter
			string printerId - the id of the print statement inside the loop (see README for question details)
 	PRE: 	All data members are intialized
 	POST: 	Returns a string of the loop
 	LOC: 	LoopsPrinters.cpp
 	EX:
 	=====================================================*/
	

	//simple getter functions
	int GetStart() { return start; };

	Symbols GetSymb() { return symb; };

	int GetStop() { return stop; };

	Symbols GetIncSymb() { return incSymb; };

	int GetIncrement() { return increment; };

protected:

 	virtual int CountIterations(int begin, Symbols symbol, int end, int inc) = 0;
	/*==================== int CountIterations(int begin, int symbol, int end, int inc) ====================
 	DESC:	This function counts the number of iterations in a for loop given the parameters.
			NOTE: even though all of these parameters are private members, I found this signature
			with the parameters easier to test. If desired, this function could be replaced or overloaded
			with no parameters, and use the private members
	PARAM:	int begin - the starting value
			Symbols symbol - the index of the comparison operator
			int end - the terminating value to compare against
			int inc - the amount to increment by
 	PRE: 	No preconditions
 	POST: 	Returns the number of times a loop executes
 	LOC: 	Loops.cpp
 	EX:
 	=====================================================*/

	virtual vector<int> ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb);
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
	Symbols symb; 		//the index of the comparison operator (i.e. <, <=, etc.)
	int stop;			//the terminating value
	Symbols incSymb;	//the index of the increment (either + or - for now)
	int increment;		//the value to change by
	int max;			//the maximum random value
};

//The below two classes hold the implementations used for most of the classes
class LinearLoops : public QLoops
{
public:
	LinearLoops() : QLoops() {};

	LinearLoops(QLoops* old) : QLoops(old) {};
	
	LinearLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	QLoops(begin, symbol, end, incSymb, inc) {};

	virtual ~LinearLoops() {};
	
	virtual void Tests();

	virtual void InitializeLoop(bool setSymb = true);

	virtual int ComputeLoop(int min = 2, int max = 8);

protected:
	int CountIterations(int begin, Symbols symbol, int end, int inc);
};

class ExpLoops : public QLoops
{
public:
	ExpLoops() : QLoops() {};

	ExpLoops(QLoops* old) : QLoops(old) {};
	
	ExpLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	QLoops(begin, symbol, end, incSymb, inc) {};

	virtual ~ExpLoops() {};
	
	virtual void Tests();

	virtual void InitializeLoop(bool setSymb = true);

	virtual int ComputeLoop(int min = 2, int max = 8);

protected:
	int CountIterations(int begin, Symbols symbol, int end, int inc);
};

//definition of simple printing functions used for loops
class ForLoopsPrinters
{
public:
	static string PrintLoop(QLoops* current, string id, string printerId);

	static string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

class WhileLoopsPrinters
{
public:
	static string PrintLoop(QLoops* current, string id, string printerId);

	static string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

class DoLoopsPrinters
{
public:
	static string PrintLoop(QLoops* current, string id, string printerId);

	static string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

#endif
