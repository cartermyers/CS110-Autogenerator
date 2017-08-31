#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include "question.h"

class Arrays : public Question 
{
public: 
	Arrays() : Question() {};
	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC: 
	LOC: Arrays.cpp
	=====================================================*/
	
private:	
	void TypeOne();
	/*==================== void TypeOne() ====================
 	DESC:	A question to simulate a swap in an array
	E.g.: 
 	=====================================================*/
	
	void TypeTwo();
	/*==================== void TypeTwo() ====================
 	DESC:	A question that increments each element int the array
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