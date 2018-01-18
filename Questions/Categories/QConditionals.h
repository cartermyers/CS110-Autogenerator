
#ifndef __QCONDITIONALS_H__
#define __QCONDITIONALS_H__

#include "question.h"

//NOTE:
//every question takes the format:
//
//	 (var1 * lit) ** (var2 * lit)
//	
//	where var1 and var2 are predeclared variables
//	lit is a literal value
// 	* is any operator of >, >=, <, <=
//	and ** is any operator of ||, &&, ==, !=
//
// 	the size of a question refers to the number of (var1 * lit) in it (refered to as parenthetical expressions
//	so a question of size 3 would be:
//	(var1 * lit) ** (var2 * lit) ** (var3 * lit)
//

class QConditionals : public Question
{
public:
	QConditionals();
	
	~QConditionals();
	
	void Tests();

private:	
	
	void InitializeExpression(int size);
	/*==================== void InitializeExpression(int size) ====================
 	DESC: 	This is the function to initialize the private data members
 	PARAM:	int size - the number of subexpressions in the who expression (see above)
 	PRE: 	None
 	POST: 	The data members below are initialized
 	LOC: 	QConditionals.cpp
 	EX:		
 	=====================================================*/	
	
	void MainQ(int size, bool randomOrder);
	/*==================== void MainQ(int size, bool randomOrder) ====================
 	DESC: 	This is the main generating function for all questions
 	PARAM:	int size - the number of subexpressions in the who expression (see above)
			bool randomOrder - an option to randomize the order of operands in the expression
 	PRE: 	None
 	POST: 	The question is finished
 	LOC: 	QConditionals.cpp
 	EX:		
 	=====================================================*/	
	
	string PrintPrompt(bool randomOrder = false);
	/*==================== string PrintPrompt(bool randomOrder = false) ====================
 	DESC: 	Print the whole prompt for the question
 	PARAM:	bool randomOrder - an option to randomize the order of the operands
 	PRE: 	The private data members are intialized
 	POST: 	Returns the question prompt to be printed
 	LOC: 	QConditionals.cpp
 	EX:		
 	=====================================================*/	
	
	bool ComputeExpression();
	/*==================== bool ComputeExpression() ====================
 	DESC: 	A wrapper function for EvalExpression that makes it easier to use and tedst
			within the context of this class
 	PARAM:	None
 	PRE: 	The private data members are intialized
 	POST: 	Returns the result of the expression
 	LOC: 	QConditionals.cpp
 	EX:		
 	=====================================================*/	
	
	//data members:
	int size;					//number of parenthetical expressions
	Expressions* expr;
	
	//question types:
	void TypeOne();
	
	void TypeTwo();
	
	void TypeThree();
	
	void TypeFour();
};

#endif