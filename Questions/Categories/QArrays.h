#ifndef __QARRAYS_H__
#define __QARRAYS_H__

#include "question.h"
#include "../Generators/Loops/ForLoops.h"

class QArrays : public Question
{
public:
	QArrays() : Question() {};
	void Tests();
	/*==================== void Tests() ====================
	This is a list of functions tested here
	FUNC:
	LOC: QArrays.cpp
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
