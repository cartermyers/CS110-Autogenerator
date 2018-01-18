
#ifndef __EXPRESSIONS_H__
#define __EXPRESSIONS_H__

#include "general.h"
#include "Variables.h"

//TODO: maybe make a function that randomizes the order that the operands appear in the expression?

class Expressions
{
public:

	//randomly generates an expression
	Expressions(unsigned int numOperands, int maxVal, VariablesVec* vars = NULL, Symbols minOperator = add, Symbols maxOperator = sub, bool differentExpressionOrder = true, bool parentheses = false);
	/*==================== Expressions() ====================
	DESC:	this function creates an expression
	PARAM:	numOperands - the number of operands in the expression
	int maxVal - the maximum value of the random operands (inclusive)
	VariablesVec* variables - an option to add variables to the expression
	Symbols minOperator - the minimum precedence of operators (inclusive)
	Symbols maxOperator - the maximum precedence of operators (inclusive)
	bool parentheses - an option to add parentheses in the expression
	NOTE: this is not currently implemented, and it will probably have some caveats when it is implemented.
	PRE: 	minOperator <= maxOperator
			numOperands > 0
	POST: 	Expression is initialized
	LOC: 	Expressions.cpp
	EX:		
	=====================================================*/

	//this constructor is mostly used for tests
	Expressions(vector<string> exp, VariablesVec* vars = NULL, bool uniqueIds = true, bool forceType = true);

	//string PrintExpr
	string Print();
	/*==================== string Print() ====================
	DESC:	this function returns an expression in a string such as "a + b - c"
	PARAM:	None
	PRE: 	None
	POST: 	A string such as "3 / b * 2" is returned
	LOC: 	Expressions.cpp
	EX:		prompt += e.Print();
	=====================================================*/

	VariablesVec GetVariables();

	vector<string> GetExpr();

	//this funciton simply randomizes the order that the variables appear in the VariablesVec
	//but it does not randomize the order that they appear in the expression
	void RandomizeVariablesDefinition();

	//float EvalExpr
	float Eval();
	/*==================== EvalExpr(bool orderOfOps = true) ====================
	DESC:	Calculates an expression with potentially non-homogenous datatypes (depending on Variables)
	PARAM:	vector<float> operands - the actual values
	vector<int> types - the datatypes of the values
	vector<int> operators - the operands in the expression
	bool orderOfOps - a parameter that is used to disregard order of ops sometimes; for wrong answers
	PRE: 	operands and types have the same size, meaning they are parallel.
	types and operators are valid indices for their respective global arrays
	operands.size() - 1 == operators.size() //only binary operators for now.
	POST: 	the result of the expression is returned as a float
	LOC: 	expression.cpp
	EX:		EvalExpr({1, 2}, {0, 1}, {1}) returns 0.5 (1 / 2.0)
	EvalExpr({1, 2}, {0, 0}, {1}) returns 0 (1 / 2)
	=====================================================*/

	//a function for generating wrong answers
	float EvalNoOrder(bool useTypes = true, bool backwards = false);

private:

	vector<string> expression;
	vector<string> postfix;
	VariablesVec variables;

	void MakePostfix();

	void E(int& currentToken);
	void A(int& currentToken);
	void B(int& currentToken);
	void C(int& currentToken);
	void D(int& currentToken);
	void T(int& currentToken);
	void F(int& currentToken);

};

#endif