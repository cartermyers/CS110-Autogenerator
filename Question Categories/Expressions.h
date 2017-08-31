#ifndef __EXPRESSIONS_H__
#define __EXPRESSIONS_H__

#include "question.h"

class Expressions : public Question {
public:
	Expressions() : Question() {};
	
	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC: 
	LOC: Expressions.cpp
	=====================================================*/
	
private:
	void MakeLiteralExpression(int max, int minTerms);
	/*==================== void MakeLiteralExpression(int, int) ====================
 	DESC:	The main question generating function for this class.
			Generates values and operators based on the max value and the
			minimum amount of terms, then calculates the expression and 
			generates wrong answers
	PARAM:	max - used to generate random values between 0 and (max - 1)
 	PRE: 	No preconditions
 	POST: 	The Question is finished
 	LOC: 	Expressions.cpp
 	EX:		
 	=====================================================*/
	
	void TypeOne();
	/*==================== void TypeOne() ====================
 	DESC:	max = 5; minterms = 2;
	E.g.: 
 	=====================================================*/
	
	void TypeTwo();
	/*==================== void TypeTwo() ====================
 	DESC:	max = 7; minterms = 3;
	E.g.: 
 	=====================================================*/
	
	void TypeThree();
	/*==================== void TypeThree() ====================
 	DESC:	max = 10; minterms = 4;
	E.g.: 
 	=====================================================*/
	
	void TypeFour();
	/*==================== void TypeFour() ====================
 	DESC:	max = 12; minterms = 5;
	E.g.: 
 	=====================================================*/
};

#endif