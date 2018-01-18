// ------------------------------------------
// general.h
// Definition of the global constants
// and some global functions for general use.
// Most libraries are also included here.
// There may also be some implementation for templated functions.
//--------------------------------------------

#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>		//used for string formating of floats
#include <vector>
#include <set>
#include <algorithm>	//used for random_shuffle()
#include <cstdlib>		//i'm not totally sure what this library is used for here
#include <cmath>
#include <cstring>
using namespace std;


//*******************************************************************************************
//							GLOBAL CONSTANTS AND ENUMERATIONS
//
//					some commonly-used and widespread representations
//*******************************************************************************************


#ifndef assert
#define assert(cond) ((cond)? (1): throw runtime_error(#cond))
#endif // !assert

//TODO: modify references of symbols

//operators:
static const vector<string> SYMBOLS = { "++", "||", "&&", "==", "!=", ">", ">=", "<", "<=", "+", "-", "*", "/", "%" };
//and an enumeration that corresponds to the vector above:
enum Symbols { incr, or, and, eq, neq, gt, gte, lt, lte, add, sub, mul, divide, mod };

//generic variable identifiers:
const vector<string> IDENTIFIERS = { "foo", "bar", "item", "list", "numbers", "matrix", "documents", "marks", "standings", "dogs" };

//TODO MOVE TO FUNCTIONS
//generic names for functions:
const vector<string> FUNCTION_IDS = { "Make", "Avg", "Sub", "Pow", "Absolute", "BinarySort", "Find", "Divide", "Calculate", "Switch" };

//just an array of the alphabet (up to n places).
//mostly used as an easy way to declare simple function parameters
const vector<string> ALPHA_LETTERS = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };

//TODO MOVE TO VARAIBLES?
//but keep here if we are supporting type coercing expressions in general

//data types IN ORDER OF ACCURACY (including "void")
const vector<string> DATA_TYPES = { "int", "float", "void" };	//NOTE: VOID SHOULD ALWAYS BE LAST ELEMENT
																//enumeration of datatypes, corresponding to the indices in DATA_TYPES
enum DataTypes { Int, Float, Void };

template <typename T, typename U, typename V>
static T Operation(Symbols Symb, U Var1, V Var2, int precision = 2);
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

float Operation(Symbols symb, float var1, DataTypes type1, float var2, DataTypes type2);
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
LOC: 	general.cpp
EX:		Operation(1, 3, 0, 5, 1); //returns 3 / 5.0 == 0.6
Operation(1, 3, 0, 5, 0); //returns 3 / 5 == 0 (really 0.0 because returns float)
=====================================================*/

string FloatToString(const float& val, bool isFixed = false, int precision = 4);
/*==================== string FloatToString(const float& answer, int precision = 4) ====================
DESC:	Returns a string value of a float with precision significant digits
PARAM:	const float& val - the value to be converted
bool isFixed - an option to always show the decimal
int precision - the number of significant digits of the float value preserved
PRE: 	No preconditions
POST: 	a string is returned
LOC: 	question.cpp
EX:
=====================================================*/

template <typename T, typename U, typename V>
T GenerateRand(U min, V max);
/*==================== T GenerateRand(U min, V max, float denominator = 1); ====================
DESC:	Generates a random number of type T with the lowest denomination of 1 / denominator
PARAM:	U min - the minimum value (inclusive)
V max - the max value to be generated (inclusive)
float denominator - the lowest denomination (e.g. if 2, the lowest denomination is 1 / 2.0 == 0.5
PRE: 	min <= max
POST: 	returns a random number
LOC: 	question.h
EX:		GenerateRand<float>(0, 5) generates from [0, 5]
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



//*******************************************************************************************
//							TEMPLATE DEFINITIONS
//
//				since i use templates with some functions, and templates are
//				ridiculous on trying to implement in a separate file,
//				i just decided to add them here
//*******************************************************************************************


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

//returns a value given two operands and an operator
template <typename T, typename U, typename V>
T Operation(Symbols symb, U var1, V var2, int precision)
{
	//scale the operands if it is a comparison 
	// (for better precision)

	if (symb == incr)
	{
		return ++var1;
	}

	if (symb <= lte)
	{
		//convert to integers
		long int temp1 = (long int)(var1 * pow(10, precision + 1) + 5) / 10;
		long int temp2 = (long int)(var2 * pow(10, precision + 1) + 5) / 10;

		switch (symb)
		{
		case gt:
			return temp1 > temp2;
		case gte:
			return temp1 >= temp2;
		case lt:
			return temp1 < temp2;
		case lte:
			return temp1 <= temp2;
		case eq:
			return temp1 == temp2;	//use this for float variables; guarantees accuracy up to 2 decimal spots (maybe need to change later?)
		case neq:
			return temp1 != temp2;
		case and:
			return temp1 && temp2;	//works for bools too
		case or :
			return temp1 || temp2;
		default:
			throw runtime_error("no operator of that type");	//hopefully never happens
		}
	}
	else
	//perform arithmetic operations
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
			return T(fmod((float)var1, (float)var2)); //use this because it works for floats and ints and the compiler doesn't whine about %
		case add:
			return var1 + var2;
		case sub:
			return var1 - var2;
		case incr:
			return var1 + 1;
		default:
			throw runtime_error("no operator of that type");	//hopefully never happens
		}
	}
}


template <typename T, typename U, typename V>
T GenerateRand(U min, V max)
{
	assert(min <= max);

	return T(min + rand() % (max - min + 1));
}

template <typename T, typename U, typename V>
T GenerateRand(U min, V max, float denominator)
{
	//this would technically still work with negative values, but it's not really intended
	//this also prevents % 0 errors
	assert(min <= max);

	return T(min + fmod(rand(), (max - min + 1) * denominator) / denominator);
}

template <typename T>
float Convert(DataTypes type, T value)
{
	if (type == Int) //int
		return float(int(value));
	else
		return float(value);
}

#endif