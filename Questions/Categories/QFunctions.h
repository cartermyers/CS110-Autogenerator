#ifndef __QFUNCTIONS_H__
#define __QFUNCTIONS_H__

#include "question.h"
#include "../Generators/Variables.h"
#include "../Generators/Expressions.h"
#include "../Generators/Functions.h"


//TODO: FIX ALL THIS AND MAKE IT REALLY READABLE AND USE OTHER DATA TYPES AND BE MODULAR
// MAKE IT SIMPLE

class QFunctions : public Question {
public:
	QFunctions() : Question() {};

	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC:
	LOC: QFunctions.cpp
	=====================================================*/

private:

	//Calculation functions (used for testing):
	float EvalAndReturnReferenceParam(VariablesVec mainScope, Functions funcScope, Expressions funcExpr, int ref, vector<float>& tempWrong);
	/*==================== string Print() ====================
	DESC:	this function evaluates a function, and returns a value that is the result of the function or the original value of a variable (depending if it is passed-by-reference in the function).
			This is a pretty niche function, so it's not really meant to be reused anywhere. It only exists for testing.
	PARAM:	VariablesVec mainScope - the variables declared in the main scope 
			Functions funcScope	- the function 
			Expressions funcExpr - the expression in the function body
			int ref - the index of the referenced variable in the main scope
			vector<float>& tempWrong - a vector for passing back wrong answers
	PRE: 	ALL STRUCTURES ARE INITIALIZED -- this means the mainScope variables have already been passed to funcScope, and the funcExpr has the values as well.
	POST: 	
	LOC: 	Expressions.cpp
	EX:		prompt += e.Print();
	=====================================================*/


	void TypeOne();
	/*==================== void TypeOne() ====================
 	DESC:
	E.g.:
 	=====================================================*/

	void TypeTwo();
	/*==================== void TypeTwo() ====================
 	DESC:
	E.g.:
 	=====================================================*/

	void TypeThree();
	/*==================== void TypeThree() ====================
 	DESC:
	E.g.:
 	=====================================================*/

	void TypeFour();
	/*==================== void TypeFour() ====================
 	DESC:
	E.g.:
 	=====================================================*/
};

#endif
