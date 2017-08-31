#ifndef __IDENTIFIERS_H__
#define __IDENTIFIERS_H__

#include "question.h"

class Identifiers : public Question
{
public:
	Identifiers();
	//this assigns random values to all of the datamembers
	
	~Identifiers() {};
	
	void Tests() {};
	//since we use the valid flag, there is really no need for testing
	//however, if we ever add a function to parse valid ids, we should test that
	
private:
	
	void GenerateRandId(bool odds = true);
	/*====================GenerateRandId(bool odds = true)====================
 	DESC: 	a function that generates the random id for the question based on the other data members
			it also has some pseudo-sampling with weights
			and it will also change the valid flag if the id is invalid
 	PARAM:	odds - the option to choose different sampling weights 
 	PRE: 	length is set
 	POST: 	The id for the function is made and the answer is generated
 	LOC: 	Identifiers.cpp
 	EX:		
 	=====================================================*/	

	void PrintAndFinish();
	/*====================PrintAndFinish()====================
 	DESC: 	a function that outputs the prompt and assigns the answers
 	PARAM:	None
 	PRE: 	the data members id and valid have been determined
 	POST: 	The question has been finished
 	LOC: 	Identifiers.cpp
 	EX:		
 	=====================================================*/	

	//some strings that make it easy to generate random chars:
	//see implementation in Identifiers.cpp
	static const string UPPER;
	
	static const string LOWER;
	
	static const string NUMBERS;
	
	static const string INVALID;
	
	//data members used in the question:
	
	string id;	//actual id
	bool valid;	//flag to know if the id is valid
	int length; //length of the id
	

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