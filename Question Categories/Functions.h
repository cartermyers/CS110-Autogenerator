#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "question.h"

class Functions : public Question {
public:
	Functions() : Question() {};
	
	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC: 
	LOC: Functions.cpp
	=====================================================*/

private:

	//temp:
	string PrintFunctionCall(const int & functionIndex, const vector<string>& ids);

	float PassAndEvalFunc(Parameters& params, vector<float> vals, vector<Symbols> operators);
	/*==================== float PassAndEvalFunc(Parameters& params, const vector<float>& vals, const vector<int> operators) ====================
 	DESC:	This takes a parameter structure, the values that are passed to it, and the operators used for an expression
			inside the function, and it returns the result of that expression. 
			NOTE: THERE ARE A LOT OF PRECONDITIONS TO THIS FUNCTION SO BE CAREFUL AND MAKE SURE YOU KNOW HOW IT'S USED
	PARAM:	Parameters& params - the parameter structure for the function
			vector<float> vals - the values to be passed as parameters
			vector<int> operators - the operators used in the functional expression
 	PRE: 	params has all of its members initialized (except vals) and 
			MOST IMPORTANTLY: the order vector is in the order of the expression!!!!!!!!!! see below
 	POST: 	The result of the expression is returned and params.vals now contains the values in vals
			NOTE: this currently doesn't take into account the function return type!
 	LOC: 	Functions.cpp
 	EX:		1) Take the following function as an example:
			void Sub(int& a, int b)
			{
				a = b - a;
			}
			
			int c = 1;
			int d = 2;
			
			Sub(d, c);
			The call should be:
			PassAndEvalFunc(params, {2, 1}, {4});
			The Parameters structure should look like this:
			params.vals = N/A
			params.dataTypes = {0, 0} 
			params.ids = {b, a}  (because of the order switch)
			params.ref = {true, false} (still in the original order)
			params.order = {1, 0} BECAUSE IT WAS RANDOMIZED
			
			So I know this is inherently confusing, but it is important
			to understand here that the order is still the same as it was used
			to change the ids from the declaration to the expression.
			
			Then, the passing of values can happen, and the params.vals is:
			params.vals = {1, 2}
			and the function is evaluated as expected:
			1 - 2 == -1
			NOTE: this also does NOT change any reference parameter values
			
			2) Here is another example to be clear
			int Div(int a, float b)
			{
				return a / b;
			}
			
			cout << Div(3.5, 4) << endl;
			
			The call:
			PassAndEvalFunc(params, {3.5, 4}, {1});
			params.vals = N/A
			params.dataTypes = {0, 1}
			params.ids = {a, b}
			params.ref = {false, false}
			params.order = {0, 1} STILL THE ORIGINAL ORDER
			
			So this works just as expected, because the order of the expression matches the parameters.
			The function computes 3 / 4 and returns 0.75, even though the return type is int.
			This is because it doesn't take the return type into account.
 	======================================================================================================*/
	

	string PrintFunctionHeader(int returnType, int funcName, const Parameters& params);
	/*==================== void MakeFunctionHeader(int returnType, int funcName, const Variables& params, const vector<bool>& refs) ====================
 	DESC:	This outputs a function header to the prompt data member
	PARAM:	int returnType - an index used in DATA_TYPES as the return type
			int funcName - and index used in FUNCTION_IDS for the name
			const Variables& params - the parameters to be printed; uses params.ids and params.dataTypes
			const vector<bool>& refs - the references for the parameters
 	PRE: 	returnType, funcName are valid indices.
			params and refs have the same size.
 	POST: 	The function header is printed out to the prompt
 	LOC: 	Functions.cpp
 	EX:		
 	=====================================================*/

	string PrintVoidFunction(Variables mainScope, Parameters& funcScope, vector<Symbols> operators, int ref, bool differentExpressionOrder);
	/*==================== string PrintVoidFunction(Variables mainScope, Parameters& funcScope, vector<Symbols> operators, int ref, bool differentExpressionOrder) ====================
 	DESC:	This outputs the general format for TypeOne()
	PARAM:	Variables mainScope - the mainScope variables
			Parameters& funcScope - the parameters in the Funciton scope
			vector<Symbols> operators - the operators used in the function
			int ref - the index of the referenced variable
			bool differentExpressionOrder - if true, randomizes the expression and the order the arguments are passed
 	PRE: 	All parameters are properly initialized
			Only Int datatype is supported right now
 	POST: 	returns the whole string of the prompt
			!!!IMPORTANT NOTE!!: If differentExpressionOrder is true, the order vector in funcScope is changed, the ids are reordered,
			but the datatypes and references are NOT. This is so we can pass the mainScope vals in the proper order and determine 
			if the assigned parameter is reference or not. 
			Please understand this before using this function because it may be unexpected or very confusing
 	LOC: 	Functions.cpp
 	EX:		
 	=====================================================*/

	float ReturnReferenceParam(Variables mainScope, Parameters funcScope, vector<Symbols> operators, int ref, vector<float>& tempWrong);
		/*==================== float ReturnReferenceParam(Variables mainScope, Parameters funcScope, vector<Symbols> operators, int ref, vector<float>& tempWrong) ====================
 	DESC:	This function actually calculates the answer for TypeOne()
	PARAM:	Variables mainScope - the mainScope variables (used for vals)
			Parameters& funcScope - the parameters in the Funciton scope
			vector<Symbols> operators - the operators used in the function
			int ref - the index of the referenced variable
			vector<float>& tempWrong - a return vector for wrong answers
 	PRE: 	The order vector in funcScope matches the order of the expression, but the refs vector in funcScope matches the original
			order of the parameters. This is the state after PrintVoidFunction is called.
 	POST: 	Returns the value of the referenced (or not referenced) parameter. Also returns wrong answers in tempWrong 
 	LOC: 	Functions.cpp
 	EX:		
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