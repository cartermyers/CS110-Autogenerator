#include "DoLoops.h"

//===============================================================================================
//===========================================LinearDoLoops Class=================================
//===============================================================================================

int LinearDoLoops::ComputeLoop(int min, int max)
{
	bool temp;
	
	//first, check if the loop condition is already satisfied
	if (symb == lt || symb == lte) //if the condition is < or <=
	{
		temp = start >= stop;			//check the opposite
	}
	else
	{
		temp = start <= stop;
	}

	//in a do while loop,
	//we have at least one loop, even if the loop condition is already met
	//else, it's just like a normal for loop
	if (temp && 1 >= min)
	{
		return 1;
	}
	else	
	{
		//return CountIterations(start, symb, stop, increment);
		return LinearLoops::ComputeLoop(min, max);
	}

	return 0;
}

vector<int> LinearDoLoops::ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb)
{
	vector<int> res;
	do
	{
		res.push_back(begin);
		begin = Question::Arithmetic(incSymb, begin, inc);
	} while (Question::Compare(symbol, begin, end));

	return res;
}

string LinearDoLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return DoLoopsPrinters::PrintLoop(current, id, printerId);
}

string LinearDoLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return DoLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}

//===============================================================================================
//============================================ExpDoLoops Class===================================
//===============================================================================================

int ExpDoLoops::ComputeLoop(int min, int max)
{
	bool temp;

	//first, check if the loop condition is already satisfied
	if (symb == lt || symb == lte) //if the condition is < or <=
	{
		temp = start >= stop;			//check the opposite
	}
	else
	{
		temp = start <= stop;
	}

	//in a do while loop,
	//we have at least one loop, even if the loop condition is already met
	if (temp && 1 >= min)
	{
		return 1;
	}
	else //else, it's just like a normal for loop
	{
		//return CountIterations(start, symb, stop, increment);
		return ExpLoops::ComputeLoop(min, max);
	}

	return 0;
}

vector<int> ExpDoLoops::ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb)
{
	//same as ShowIterations for the LinearDoLoops
	//but i can't figure out how not to copy over the access :(

	vector<int> res;

	do
	{
		res.push_back(begin);
		begin = Question::Arithmetic(incSymb, begin, inc);
	} while (Question::Compare(symbol, begin, end));

	return res;
}

string ExpDoLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return DoLoopsPrinters::PrintLoop(current, id, printerId);
}

string ExpDoLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return DoLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}

//===============================================================================================
//================================================ Tests ========================================
//===============================================================================================

void LinearDoLoops::Tests()
{	
	//use a temporary class to easily initialize data members
	QLoops* test;
	
	//check to make sure a couple regular cases work
	test = new LinearDoLoops(0, lt, 4, add, 1);
	assert(test->ComputeLoop(1, 10) == 4);
	delete test;
	
	test = new LinearDoLoops(0, lte, 4, add, 1);
	assert(test->ComputeLoop(1, 10) == 5);
	delete test;
	
	test = new LinearDoLoops(6, gt, 2, sub, 1);
	assert(test->ComputeLoop(1, 10) == 4);
	delete test;
	
	test = new LinearDoLoops(7, gte, 3, sub, 2);
	assert(test->ComputeLoop(1, 10) == 3);
	delete test;
	
	//now only check special cases
	test = new LinearDoLoops(5, lt, 3, add, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new LinearDoLoops(6, lte, 3, sub, 3);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new LinearDoLoops(4, gt, 4, add, 1);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new LinearDoLoops(0, gte, 3, add, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new LinearDoLoops(5, lte, 5, add, 1);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
}

void ExpDoLoops::Tests()
{
	QLoops* test;

	//check for a couple of regular cases
	test = new ExpDoLoops(1, lt, 8, mul, 2);
	assert(test->ComputeLoop(1, 10) == 3);
	delete test;
	
	test = new ExpDoLoops(1, lt, 7, mul, 2);
	assert(test->ComputeLoop(1, 10) == 3);
	delete test;
	
	test = new ExpDoLoops(1, lt, 9, mul, 2);
	assert(test->ComputeLoop(1, 10) == 4);
	delete test;
	
	test = new ExpDoLoops(1, lte, 8, mul, 2);
	assert(test->ComputeLoop(1, 10) == 4);
	delete test;
	
	test = new ExpDoLoops(7, gt, 3, divide, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new ExpDoLoops(7, gte, 3, divide, 2);
	assert(test->ComputeLoop(1, 10) == 2);
	delete test;
	
	test = new ExpDoLoops(9, gt, 3, divide, 2);
	assert(test->ComputeLoop(1, 10) == 2);
	delete test;
	
	//now only check special cases for Do Loops
	
	test = new ExpDoLoops(1, gt, 1, divide, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new ExpDoLoops(7, lt, 3, divide, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new ExpDoLoops(8, gt, 9, mul, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
	test = new ExpDoLoops(8, gt, 8, mul, 2);
	assert(test->ComputeLoop(1, 10) == 1);
	delete test;
	
}