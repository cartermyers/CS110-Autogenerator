// ------------------------------------------
// question.h
// Definition of the Question class 
// with some implementation of templated functions
//--------------------------------------------


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

#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>		//used for string formating of floats
#include <vector>
#include <set>
#include <algorithm>	//used for random_shuffle()
#include <assert.h>
#include <cstdlib>		//i'm not totally sure what this library is for
#include <cmath>
using namespace std;

//*******************************************************************************************
//							GLOBAL CONSTANTS AND ENUMERATIONS
//
//					some commonly-used and widespread representations
//*******************************************************************************************

//note: maybe I should split up the symbols?
//how often do I want the comparison operators and the arithmetic operators in the same place?
//the only benefit to this is that they can both be used easily in Arithmetic

//operators:
static const vector<string> SYMBOLS = { "*", "/", "%", "+", "-", "++", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };
//and an enumeration that corresponds to the vector above:
enum Symbols { mul, divide, mod, add, sub, incr, gt, gte, lt, lte, eq, neq, and, or };

//generic variable identifiers:
const vector<string> IDENTIFIERS = { "foo", "bar", "item", "list", "numbers", "matrix", "documents", "marks", "standings", "dogs" };

//generic names for functions:
const vector<string> FUNCTION_IDS = { "Make", "Avg", "Sub", "Pow", "Absolute", "BinarySort", "Find", "Divide", "Calculate", "Switch" };

//just an array of the alphabet (up to n places).
//mostly used as an easy way to declare simple function parameters
const vector<string> ALPHA_LETTERS = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };

//data types IN ORDER OF ACCURACY (including "void")
const vector<string> DATA_TYPES = { "int", "float", "void" };	//NOTE: VOID SHOULD ALWAYS BE LAST ELEMENT
//enumeration of datatypes, corresponding to the indices in DATA_TYPES
enum DataTypes { Int, Float, Void };


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
	
	//make this function public and static because it is useful outside of the class scope
	//and it isn't really harmful
	template <typename T>
	static T Arithmetic(Symbols Symb, T Var1, T Var2);
	/*==================== T Arithmetic(int Symb, T Var1, T Var2) ====================
 	DESC:	Performs a computation on two variables given an index used in SYMBOLS
	PARAM:	int Symb - the index of the operation to be performed
			T Var1 - the first variable in the expression
			T Var2 - the second variable
 	PRE: 	Symb is in the range of SYMBOLS
 	POST: 	an answer of the operation is returned
 	LOC: 	question.h
 	EX:		int foo = Arithmetic<int>(3, 4, 5); //performs 4 + 5 
 	=====================================================*/

	template <typename T, typename U>
	static bool Compare(Symbols symb, const T& a, const U& b, int precision = 2);
	/*==================== bool IsSame(const T& a, const U& b, int precision = 2) ====================
	DESC:	Given two values, see if they are equal up to precision decimal points
	PARAM:	const T& a - value 1
	const U& b - value 2
	int precision - the number of decimal places to compare (default is 2)
	PRE: 	No preconditions
	POST: 	Returns true or false if the elements are equal up to the given precision
	LOC: 	question.h
	EX:		if (IsSame<float, int>(1.001, 1)) ... //returns true
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
	
	string PrintExpr(const vector<string>& operandIds, const vector<Symbols>& operators);
	/*==================== string PrintExpr(vector<string>& operandIds, vector<int>& operators) ====================
 	DESC:	Given all of the operands and operators, this function returns an expression in a string
			such as "a + b - c"
	PARAM:	const vector<string>& operandIds - literal strings of the operands (e.g. "a", "2")
			const vector<int>& operators - the indices of the operators in SYMBOLS
			
			NOTE: I only use const reference to vectors because it is read only and memory efficient.
			If you want to use vector literals, change the parameters to pass by value.
 	PRE: 	operandIds.size() - 1 == operators.size(), because it doesn't support unary operators yet
 	POST: 	A string such as "3 / b * 2" is returned
 	LOC: 	question.cpp
 	EX:		prompt += PrintExpr(operands, operators); //only declared vectors
 	=====================================================*/

	int FindUnique(const vector<int>& A, int lengthA, int range);
	/*==================== int FindUnique(vector<int>& A, int lengthA, int range) ====================
 	DESC:	Returns a new random value from 0 to (range - 1) into A that is not already in A 
	PARAM:	const vector<int>& A - the vector to compare
			int lengthA - an explicit number of elements in A
			int range - the value used to generate random numbers in range 0 to (range - 1)
 	PRE: 	range > lengthA //this isn't a very good condition but guarantees the loop terminates
 	POST: 	an element that is not in A is returned
 	LOC: 	question.cpp
 	EX:		A.push_back(FindUnique(A, A.size(), 5));
 	=====================================================*/

	float Arithmetic(Symbols symb, float var1, DataTypes type1, float var2, DataTypes type2);
	/*==================== float Arithmetic(int symb, float var1, int type1, float var2, int type2) ====================
	DESC:	Performs an operation on var1 and var2 given their datatypes
	PARAM:	int symb - the index of the operator
			float var1 - the value of var1
			int type1 - the datatype of var1
			float var2 - the value of var2
			int type2 - the datatype of var2
	PRE: 	symb is a valid index for SYMBOLS;
			type1 and type2 are valid indices for DATA_TYPES
	POST: 	the result of the operation is returned
	LOC: 	question.cpp
	EX:		Arithmetic(1, 3, 0, 5, 1); //returns 3 / 5.0 == 0.6
			Arithmetic(1, 3, 0, 5, 0); //returns 3 / 5 == 0 (really 0.0 because returns float)
	=====================================================*/

	float EvalExpr(vector<float> operands, vector<DataTypes> types, vector<Symbols> operators, bool orderOfOps = true);
	/*==================== float EvalExpr(vector<float> operands, vector<int> types, vector<int> operators, bool orderOfOps = true) ====================
	DESC:	Calculates an expression with potentially non-homogenous datatypes
	PARAM:	vector<float> operands - the actual values
			vector<int> types - the datatypes of the values
			vector<int> operators - the operands in the expression
			bool orderOfOps - a parameter that is used to disregard order of ops sometimes; for wrong answers
	PRE: 	operands and types have the same size, meaning they are parallel.
			types and operators are valid indices for their respective global arrays
			operands.size() - 1 == operators.size() //only binary operators for now.
	POST: 	the result of the expression is returned as a float
	LOC: 	question.cpp
	EX:		EvalExpr({1, 2}, {0, 1}, {1}) returns 0.5 (1 / 2.0)
			EvalExpr({1, 2}, {0, 0}, {1}) returns 0 (1 / 2)
	=====================================================*/

	string FloatToString(const float& val, bool isFixed = false, int precision = 4);
	/*==================== string FloatToString(const float& answer, int precision = 4) ====================
	DESC:	Returns a string value of a float with precision significant digits
	PARAM:	const float& answer - the value to be converted
			bool isFixed - an option to always show the decimal
			int precision - the number of significant digits of the float value preserved
	PRE: 	No preconditions
	POST: 	a string is returned
	LOC: 	question.cpp
	EX:		
	=====================================================*/
	
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

	template <typename T>
	T EvalExpr(vector<T> operands, vector<Symbols> operators, bool orderOfOps = true);
	/*==================== T EvalExpr(vector<T> operands, vector<int> operators, bool orderOfOps = true) ====================
 	DESC:	Executes an expression given the operands and indices of operators
	PARAM:	vector<T> operands - the actual values in the expression
			vector<T> operators - the indices to access SYMBOLS
			bool orderOfOps - an optional parameter used to evaluate expressions in the wrong order
 	PRE: 	All elements of operators are in the range of SYMBOLS
			operands.size() - 1 == operators.size() // no support for unary operators yet
 	POST: 	an answer of the expression is returned
 	LOC: 	question.h
 	EX:		int foo = EvalExpr<int>({2, 4, 3}, {3, 1}); //performs 2 + 4 / 3 == 3
 	=====================================================*/

	template <typename T>
	T EvalExprBackwards(vector<T> operands, vector<Symbols> operators);
	/*==================== T EvalExprBackwards(vector<T> operands, vector<int> operators) ====================
 	DESC:	Executes an expression given the operands and indices of operators but backwards
	PARAM:	vector<T> operands - the actual values in the expression
			vector<T> operators - the indices to access SYMBOLS
 	PRE: 	All elements of operators are in the range of SYMBOLS
			operands.size() - 1 == operators.size() // no support for unary operators yet
 	POST: 	a wrong answer of the expression is returned
 	LOC: 	question.h
 	EX:		int foo = EvalExpr<int>({4, 2, 3}, {1, 3}); //performs 4 / 2 + 3 == 0 (first 2 + 3 then 4 / 2)
 	=====================================================*/

	template <typename T>
	void MakeExpr(vector<T>& operands, vector<Symbols>& operators, const int& max, Symbols operatorMax = sub);
	/*==================== void MakeExpr(vector<T>& operands, vector<int>& operators, const int& max) ====================
 	DESC:	This function 'makes' a random expression, given preallocated vectors of operands and operators and a max random value
	PARAM:	vector<T>& operands - a preallocated vector to be assigned new values
			vector<T>& operators - a preallocated vector to be assigned new values of indices in SYMBOLS
			const int& max - the maximum value of random values (actually up to max - 1)
 	PRE: 	operands.size() - 1 == operators.size() // no support for unary operators yet
 	POST: 	Operands is overwritten and all elements are in the range 0 to (max - 1)
			Operators is overwritten and all elements are in the range of SYMBOLS
 	LOC: 	question.h
 	EX:		MakeExpr<float>(vals, ops, 10);	//assigns values to vals and ops
 	=====================================================*/

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

	template <typename T, typename U, typename V>
	T Question::GenerateRand(U min, V max);
	/*==================== T GenerateRand(U min, V max, float denominator = 1); ====================
	DESC:	Generates a random number of type T with the lowest denomination of 1 / denominator
	PARAM:	U min - the minimum value (inclusive)
	V max - the max value to be generated (exclusively)
	float denominator - the lowest denomination (e.g. if 2, the lowest denomination is 1 / 2.0 == 0.5
	PRE: 	min < max
	POST: 	returns a random number
	LOC: 	question.h
	EX:		GenerateRand<float>(0, 5) generates from [0, 5) 
	=====================================================*/

	template <typename T, typename U, typename V>
	T GenerateRand(U min, V max, float denominator);
	/*==================== T GenerateRand(U min, V max, float denominator); ====================
	DESC:	Generates a random number of type T with the lowest denomination of 1 / denominator
	PARAM:	U min - the minimum value (inclusive)
			V max - the max value to be generated (exclusively)
			float denominator - the lowest denomination (e.g. if 2, the lowest denomination is 1 / 2.0 == 0.5
	PRE: 	min < max
	POST: 	returns a random number
	LOC: 	question.h
	EX:		GenerateRand<float>(0, 1, 2) generates [0, 1) in 0.5 intervals
			GenerateRand<float>(0, 1, 3) generates [0, 1) in 0.333 intervals
			GenerateRand<float>(0, 10, 2) generates [0, 10) in 0.5 intervals
	=====================================================*/
	
	template <typename T>
	float Convert(DataTypes type, T value);
	/*==================== float Convert(int type, T value) ====================
	DESC:	Converts a value into a given data type in DATA_TYPES
			NOTE: this isn't to be used as an actual conversion!!!!
			This is simply a simulation of type coercion
	PARAM:	int type - the index of the data type to be converted to
			T value - the actual value to be converted
	PRE: 	type is a valid index of DATA_TYPES (but not "void")
	POST: 	returns a float of the "new type" (see examples below)
	LOC: 	question.h
	EX:		Convert(0, 1.5); //returns 1.0
			Convert(1, 1); //returns 1.0
			Covert(0, OperandSwitch(
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

//This is a simple data structure that can be quite useful.
//It is meant to represent all variables in a given scope.
//All vectors are in parallel, but sometimes its nice to 
//randomly reorder them simultaneously. This is what the order vector is for

//CONSIDER CREATING A TEMPLATE CLASS FOR THIS
struct Variables {

	int size;					//how many variables in the scope
	vector<DataTypes> dataTypes;		//index used to access a datatype in DATA_TYPES[]; keep as int because its easy to compare
	vector<string> ids;			//names of variables
	vector<float> vals;			//corresponding values of variables; always be float because it is most general case we deal with
	vector<int> order;			//order to access everything (default is 0, 1, ... n-1)
								
	Variables();
	/*==================== Variables() ====================
	DESC:	A basic constructor 
	PARAM:	No parameters
	PRE: 	No preconditions
	POST: 	size is set to 0
	LOC: 	question.cpp
	EX:		
	=====================================================*/
	
	Variables(int length);
	/*==================== Variables(int length) ====================
	DESC:	A basic constructor based on the desired length
	PARAM:	int length - the number of variables in Variables
	PRE: 	No preconditions
	POST: 	All data members are superficially initialized, with size = length
	LOC: 	question.cpp
	EX:		
	=====================================================*/
	
	Variables(vector<DataTypes> types, vector<float> values, vector<string> identifiers);
	/*==================== Variables(vector<int> types, vector<float> values, vector<string> identifiers) ====================
	DESC:	An explicit constructor for some data members
	PARAM:	vector<int> types - the indices of datatypes for each element
			vector<float> values - the actual values
			vector<string> identifiers - the ids for each variable
	PRE: 	All parameters have the same size
	POST: 	All the parameters are assigned to the data members, and all other data members are initialized
	LOC: 	question.cpp
	EX:		
	=====================================================*/

	void ReorderStructure();
	/*==================== void ReorderStructure() ====================
	DESC:	This function reorders each member function based on the order of indices in order
	PARAM:	No parameters
	PRE: 	All member vectors are initialized with the same length.
			All elements in order are valid indices
	POST: 	All the member vectors are reordered
	LOC: 	question.cpp
	EX:		
	=====================================================*/

	template <typename T>
	void ReorderStructure(vector<T>& old);
	/*==================== void ReorderStructure(vector<T>& old) ====================
	DESC:	Reorders the given vector based on the indices in order
	PARAM:	vector<T>& old - the original vector
	PRE: 	old initialized with the same length as order.
			All elements in order are valid indices.
	POST: 	old is reordered
	LOC: 	question.h
	EX:		
	=====================================================*/
};

//have a structure just like variables but for functions.
//each parameter can be thought of exactly like a variable
//except it can be reference or not.
struct Parameters : public Variables 
{
	Parameters();
	
	Parameters(int size);
	
	//explicit constructor
	Parameters(vector<DataTypes> types, vector<float> values, vector<string> identifiers, vector<bool> ref);
	
	//an overload of ReorderStructure to allow for the new members below (like refs)
	void ReorderStructure();
	
	vector<bool> refs;		//keeps track if the parameter is reference
};

//*******************************************************************************************
//							QUESTIONS SUPERCLASS TEMPLATE DEFINITIONS	
//
//				since i use templates with some functions, and templates are 
//				ridiculous on trying to implement separately, 
//				i just decided to add them here
//*******************************************************************************************

//MAYBE THIS SHOULD BE IN FUNCTIONS
//or in Variables?
//it's only used there
//although I see where we might use it somewhere else
template <typename T>
float Question::Convert(DataTypes type, T value)
{
	if (type == 0) //int
		return float(int(value));
	else
		return float(value);
}

template <typename T, typename U, typename V>
T Question::GenerateRand(U min, V max)
{
	assert(min < max);

	return T(min + rand() % (max - min));
}

template <typename T, typename U, typename V>
T Question::GenerateRand(U min, V max, float denominator)
{
  //this would technically still work with negative values, but it's not really intended
  //this also prevents % 0 errors
  assert(min < max);
  
  return T(min + fmod(rand(), (max - min) * denominator) / denominator);
}

//returns a value given two operands and an operator
template <typename T>
T Question::Arithmetic(Symbols symb, T var1, T var2)
{
	switch (symb)
	{
	case mul:
		return var1 * var2;
	case divide:
		if (var2 == 0)	//should only occur in wrong answer generations
			return 0;	//so just give a useless value
		return var1 / var2;
	case mod:
		if (var2 == 0) //same as above
			return var1;
		return T(fmod(var1, var2)); //use this because it works for floats and ints and the compiler doesn't whine about %
	case add:
		return var1 + var2;
	case sub:
		return var1 - var2;
	case incr:
		return var1 + 1;
	default:
		return 0;
	}
}

//compare two numbers  
//up to (precision) number of decimal points
//(can be negative for less precision)
//
//GENERAL NOTE: Do not assume a higher precision will fit your needs.
//Take the following example:
// ans1 = 25.5678
// ans2 = 25.5744
// if you did cout << setprecision(4); WITH NO FIXED
// and called Compare(eq, ans1, ans2, 4)
// it would return false, but you would print out:
// 25.57
// 25.57
//
// This may be obvious, but I just wanted to make it clear.
template <typename T, typename U>
bool Question::Compare(Symbols symb, const T& a, const U& b, int precision)
{
	//convert to integers
	long int var1 = (long int)(a * pow(10, precision + 1) + 5) / 10;
	long int var2 = (long int)(b * pow(10, precision + 1) + 5) / 10; 

	switch (symb)
	{
	case gt:
		return var1 > var2;
	case gte:
		return var1 >= var2;
	case lt:
		return var1 < var2;
	case lte:
		return var1 <= var2;
	case eq:
		return var1 == var2;	//use this for float variables; guarantees accuracy up to 2 decimal spots (maybe need to change later?)
	case neq:
		return var1 != var2;
	case and:
		return var1 && var2;	//works for bools too
	case or:
		return var1 || var2;
	default:
		return false;	//hopefully never happens
	}
}

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
			
			if (Compare<U, T>(eq, tempWrong[i], tempCorrect, precision))
			{
				tempWrong[i] = Arithmetic<U>(GenerateRand<Symbols>(add, sub + 1), tempWrong[i], GenerateRand<U>(1, 3, 2));
				//don't need to change the unique flag here because it'll be checking the others in the next for loop anyway
			}
	
			//check against EVERY other element in the array
			for (size_t j = i + 1; j < (n + i); j++)
			{
				if (Compare<U, U>(eq, tempWrong[i], tempWrong[j % n], precision))
				{
					tempWrong[i] = Arithmetic<U>(GenerateRand<Symbols>(add, sub + 1), tempWrong[i], GenerateRand<U>(1, 3, 2));
					unique = false;	//now that we've changed this element we need to recheck it
					break;			//so don't bother comparing the new value because we'll be rechecking against all values again
				}
			}
		} while (!unique);
	}
}

//Return an integer, based off the operands and operators in the expression
//assumes that operands.size() - 1 = operators.size() -- which is pretty normal
//write documentation later
template <typename T>
T Question::EvalExpr(vector<T> operands,	//actual values
					 vector<Symbols> operators, //ints representing operators by index
					 bool orderOfOps)		//default true; chooses to follow the order of operations or not
{
	//change this assertion later when supporting ++ operator
	assert(operands.size() - 1 == operators.size());

	if (orderOfOps)
	{
		//first check for *, / or % operators:
		for (size_t i = 0; i < operators.size();) //i updated in loop
		{
			if (operators[i] <= 2)
			{
				operands[i] = Arithmetic<T>(operators[i], operands[i], operands[i + 1]);
				operators.erase(operators.begin() + i);		//erase the operator because we no longer need it
				operands.erase(operands.begin() + i + 1);	//and erase the second operand because it was used as well (the first one was written over)
			}
			else
			{
				i++; //move on to next element
			}
		}
	}

	//now do all the other operators:
	while (operators.size() > 0) 
	{
		operands[0] = Arithmetic<T>(operators[0], operands[0], operands[1]);
		operators.erase(operators.begin());		//use same logic as above
		operands.erase(operands.begin() + 1);
	}

	return operands[0];
}

template <typename T>
T Question::EvalExprBackwards(vector<T> operands, vector<Symbols> operators)
{
	//change when supporting for ++
	assert(operands.size() - 1 == operators.size());

	for (int i = operators.size() - 1; i >= 0; i--)
	{
		operands[i] = Arithmetic<T>(operators[i], operands[i], operands[i + 1]);
		//we could delete elements in the vectors here since we are no longer using them
		//but it doesn't aid performance, and it doesn't matter for the loop
		//this is because we aren't considering order of operations (which seems silly for wrong answers)
	}

	return operands[0];
}

//a function that randomly generates the operands and operators of an expression
//right now only supports +, -, /, *, and % operators
//maybe add a parameter so we could choose a range of operators
template <typename T>
void Question::MakeExpr(vector<T>& operands,	//preallocated vector that will be rewritten values 
						vector<Symbols>& operators, //same as above, except for indicies to reference SYMBOLS; assumes operands.size() - 1 == operators.size()
						const int& max,			//maximum value to be used in the operands
						Symbols operatorMax)	//picks operators between 0 to this operator	
{
	assert(operands.size() - 1 == operators.size());

	operands[0] = GenerateRand<T>(2, max, 2);

	//and place rest of values along with operators:
	for (size_t i = 0; i < operators.size(); i++)
	{
		Symbols temp = GenerateRand<Symbols>(0, operatorMax + 1); //this chooses our operator

		//try to get some different operators
		if (i > 0)
		{
			while (temp == operators[i - 1])
			{
				temp = GenerateRand<Symbols>(0, operatorMax + 1);
			}
		}
		
		operators[i] = temp;
		operands[i + 1] = GenerateRand<T>(2, max, 2);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
//reorder all the vectors based on the order vector
template <typename T>
void Variables::ReorderStructure(vector<T>& old)
{
	for (int i = 0; i < size; i++)
	{
		//first just append the values so we have the old order to reference
		old.push_back(old[order[i]]);
	}
	//and erase the last parts:
	old.erase(old.begin(), old.begin() + size);
}

#endif