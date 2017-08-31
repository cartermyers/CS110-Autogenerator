#include "QLoops.h"

//===============================================================================================
//=================================QLoops Class and Subclasses===================================
//===============================================================================================

QLoops::QLoops()
{
	//just superficially set all members
	//they should be handled in the InitializeLoop() function
	symb = Symbols(-1);
	max = -1;
	start = -1;
	stop = -1;
	increment = -1;
	incSymb = Symbols(-1);
}

QLoops::QLoops(QLoops* old)
{
	symb = old->GetSymb();
	start = old->GetStart();
	stop = old->GetStop();
	increment = old->GetIncrement();
	incSymb = old->GetIncSymb();
}

//implement these two functions here because they are almost the same for every class
//except do while
vector<int> QLoops::ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incrementSymb)
{
	vector<int> res;
	
	while (Question::Compare(symbol, begin, end))
	{
		res.push_back(begin);
		begin = Question::Arithmetic(incrementSymb, begin, inc);
	}
	
	return res;
}

vector<int> QLoops::ShowLoop(int min, int max)
{
	ComputeLoop(min, max); //so we count the number of iterations and then change them to be between min and max
	
	return ShowIterations(start, symb, stop, increment, incSymb);
}

//===============================================================================================
//=========================================Linear Loops=========================================
//===============================================================================================
void LinearLoops::InitializeLoop(bool setSymb)
{
	if (setSymb)
	{
		//symb = GenerateRand<Symbols>(gt, lte + 1);
		symb = Symbols(gt + rand() % (lte - gt + 1)); //uses whole range of loops operators
	}

	max = 5 + rand() % 5;

	//generate the start and the stop assuming that it's a lt '>' sign
	start = 2 + rand() % max;
	stop = start + rand() % max;
	incSymb = add;

	//set increment and scale the stop value if needed
	switch (rand() % 3)
	{
	case 0:
		increment = 1;
		break;
	case 1:
		start = start * 5 + rand() % max;
		stop = stop * 5 + rand() % max;
		increment = 5;
		break;
	case 2:
		start = start * 10 + rand() % max;
		stop = stop * 10 + rand() % max;
		increment = 10;
		break;
	}

	//and swap the start and the stop values if our initial assumption of the symbol was wrong
	if (symb == gt || symb == gte)  //> or >=
	{
		incSymb = sub;
		int temp = start;
		start = stop;
		stop = temp;
	}
}

int LinearLoops::ComputeLoop(int min, int max)
{
	assert(min < max);

	int estIterations = min + (max - min) / 2; //roughly how many iterations we want (in the middle)

	//i think this function call works fine without the scope resolution
	//but I just want to be positive
	int temp = LinearLoops::CountIterations(start, symb, stop, increment);

	//check to see if the loop runs at least min, and no more than max times
	//modify the loop condition if necessary

	if (temp < min || temp > max)
	{
		int estIterations = min + (max - min) / 2; //roughly how many iterations we want (in the middle)

		if (symb == gt || symb == gte) //> or >=
		{
			stop = start - estIterations * increment;
			//due to our counting algorithm, all values must be nonnegative so
			if (stop < 0)
			{
				start -= stop;
				stop = 0;
			}
		}
		else //< or <=
		{
			stop = start + estIterations * increment;
		}
		//and recount the loop
		temp = LinearLoops::CountIterations(start, symb, stop, increment);
	}
	return temp;
}

int LinearLoops::CountIterations(int begin, Symbols symbol, int end, int inc)
{
	assert(begin >= 0 && end >= 0);

	//just some quick logic to check for degenerative cases
	if (symbol == gt || symbol == gte)
	{
		if (begin < end)
		{
			return 0;
		}
	}
	else
	{
		if (begin > end)
		{
			return 0;
		}
	}

	int diff = abs(begin - end);
	int temp = diff / inc;

	//this checks if we need to add an extra iteration (because the diff is not completely divisible)
	if (diff % inc != 0)
	{
		temp++;
	}
	else if (symbol == lte || symbol == gte) //this means it is completely divisible, but we only add one for '<=' or '>=' cases
	{
		temp++;
	}

	return temp;
}

//===============================================================================================
//===========================================Exp Loops===========================================
//===============================================================================================

void ExpLoops::InitializeLoop(bool setSymb)
{
	//i'm not sure how often max is used?
	//but i'll initialize it here anyway
	max = 10 + rand() % 10;

	//only initialize the symb if it is explicitly stated
	if (setSymb)
	{
		symb = Symbols(gt + rand() % (lte - gt + 1)); //use the whole range of loop operators
	}

	start = 1 + rand() % 4; //always have a fairly low start

							//set the increment (either 2 or 10 cause those are easy powers)
	if (rand() % 2)
	{
		increment = 2;
	}
	else
	{
		increment = 10;
	}

	stop = int(start * pow(increment, 1 + rand() % 3)); //gives roughly between 1 and 3 iterations

														//and add this random end to make it look "less nice"
														//and it may add another loop or two
	stop += rand() % (stop * increment);

	if (symb == gt || symb == gte) //> or >=
	{
		incSymb = divide; // /
						  //need to swap the start and stops
		int temp = start;
		start = stop;
		stop = temp;
	}
	else
	{
		incSymb = mul; // *
					   // no need to swap
	}
}

int ExpLoops::ComputeLoop(int min, int max)
{
	int temp = ExpLoops::CountIterations(start, symb, stop, increment);

	if (temp < min || temp > max)
	{
		int estIterations = min + (max - min) / 2; //roughly how many iterations we want
		int diff = int(pow(increment, estIterations));  //the difference needed for that many iterations

		if (symb == gt || symb == gte)
		{
			stop = start / diff;

			if (stop <= 0)
			{
				start = diff;
				stop = 1;
			}
		}
		else
		{
			stop = start * diff;
		}
		temp = ExpLoops::CountIterations(start, symb, stop, increment);
	}

	return temp;
}

int ExpLoops::CountIterations(int begin, Symbols symbol, int end, int inc)
{
	assert(begin >= 0 && end >= 0);

	int ans;
	int termValue; //the value that makes the loop 'terminate'

	//NOTE: there's no particular reason I use log2 here
	//except it might be a bit faster since we use 2 as the base a lot
	//I haven't really looked for any proof though
	//we could easily use log or log10

	//floor is used for /= and ceil is used for *=
	// these correspond to the condition symbol
	//also the begin and end spots are switched
	
	if (symbol == gt || symbol == gte) //> or >=
	{
		ans = int(floor(log2(double(begin) / end) / log2(inc)));
		termValue = int(begin / pow(inc, ans));

		//this is accounts for weird integer division
		if (termValue > end)
		{
			ans++;
		}
	}
	else
	{
		ans = int(ceil(log2(double(end) / begin) / log2(inc)));
		termValue = int(begin * pow(inc, ans));
	}

	//the following is true only about 3.75% of the time
	//should i change the initialization to make it more common?

	//if the symbol contains a '=' and if the termValue is equal to the end condition
	//we need to add one
	if (termValue == end && (symbol == gte || symbol == lte))
	{
		ans++;
	}

	return ans;
}

//===============================================================================================
//=============================================Tests=============================================
//===============================================================================================

void LinearLoops::Tests()
{
	//for (int i = 0; i < 5; i += 1)
	assert(CountIterations(0, lt, 5, 1) == 5);
	//for (int i = 0; i < 5; i += 2)
	assert(CountIterations(0, lt, 5, 2) == 3);
	//for (int i = 0; i < 6; i += 2)
	assert(CountIterations(0, lt, 6, 2) == 3);
	//for (int i = 0; i < 0; i += 1)
	assert(CountIterations(0, lt, 0, 1) == 0);

	//for (int i = 0; i <= 0; i += 1)
	assert(CountIterations(0, lte, 0, 1) == 1);
	//for (int i = 0; i <= 5; i += 1)
	assert(CountIterations(0, lte, 5, 1) == 6);
	//for (int i = 0; i <= 6; i += 2)
	assert(CountIterations(0, lte, 6, 2) == 4);
	//for (int i = 0; i <= 5; i += 2)
	assert(CountIterations(0, lte, 5, 2) == 3);

	//for (int i = 4; i > 0; i -= 1)
	assert(CountIterations(4, gt, 0, 1) == 4);
	//for (int i = 4; i > 0; i -= 2)
	assert(CountIterations(4, gt, 0, 2) == 2);
	//for (int i = 3; i > 0; i -= 2)
	assert(CountIterations(3, gt, 0, 2) == 2);
	//for (int i = 0; i > 0; i -= 2)
	assert(CountIterations(0, gt, 0, 2) == 0);

	//for (int i = 0; i >= 0; i -= 1)
	assert(CountIterations(0, gte, 0, 1) == 1);
	//for (int i = 3; i >= 1; i -= 1)
	assert(CountIterations(3, gte, 1, 1) == 3);
	//for (int i = 6; i >= 1; i -= 2)
	assert(CountIterations(6, gte, 1, 2) == 3);
	//for (int i = 6; i >= 0; i -= 2)
	assert(CountIterations(6, gte, 0, 2) == 4);
}

void ExpLoops::Tests()
{
	//right now, I'm only adding test cases for *= 2 and /= 10 and all those combinations
	//but if we wish to use different increment amounts in the future, it's a good idea to add more test cases

	// 			<

	//for (int i = 1; i < 8; i *= 2)
	assert(CountIterations(1, lt, 8, 2) == 3);
	//for (int i = 2; i < 8; i *= 2)
	assert(CountIterations(2, lt, 8, 2) == 2);
	//for (int i = 3; i < 8; i *= 2)
	assert(CountIterations(3, lt, 8, 2) == 2);
	//for (int i = 1; i < 9; i *= 2)
	assert(CountIterations(1, lt, 9, 2) == 4);
	//for (int i = 1; i < 7; i *= 2)
	assert(CountIterations(1, lt, 7, 2) == 3);
	//for (int i = 1; i < 5; i *= 2)
	assert(CountIterations(1, lt, 7, 2) == 3);
	//for (int i = 5; i < 19; i *= 2)
	assert(CountIterations(5, lt, 19, 2) == 2);

	//for (int i = 2; i < 18; i *= 10)
	assert(CountIterations(2, lt, 18, 10) == 1);
	//for (int i = 3; i < 3578; i *= 10)
	assert(CountIterations(3, lt, 3578, 10) == 4);
	//for (int i = 3; i < 3000; i *= 10)
	assert(CountIterations(3, lt, 3000, 10) == 3);
	//for (int i = 3; i < 3001; i *= 10)
	assert(CountIterations(3, lt, 3001, 10) == 4);

	//			<=

	//for (int i = 1; i <= 8; i *= 2)
	assert(CountIterations(1, lte, 8, 2) == 4);
	//for (int i = 1; i <= 9; i *= 2)
	assert(CountIterations(1, lte, 9, 2) == 4);
	//for (int i = 1; i <= 7; i *= 2)
	assert(CountIterations(1, lte, 7, 2) == 3);
	//for (int i = 2; i <= 8; i *= 2)
	assert(CountIterations(2, lte, 8, 2) == 3);
	//for (int i = 6; i <= 48; i *= 2)
	assert(CountIterations(6, lte, 48, 2) == 4);
	//for (int i = 6; i <= 47; i *= 2)
	assert(CountIterations(6, lte, 47, 2) == 3);
	//for (int i = 1; i <= 1; i *= 2)
	assert(CountIterations(1, lte, 1, 2) == 1);

	//for (int i = 3; i <= 3000; i *= 10)
	assert(CountIterations(3, lte, 3000, 10) == 4);
	//for (int i = 3; i <= 3001; i *= 10)
	assert(CountIterations(3, lte, 3001, 10) == 4);
	//for (int i = 4; i <= 476; i *= 10)
	assert(CountIterations(4, lte, 476, 10) == 3);
	//for (int i = 5; i <= 5; i *= 10)
	assert(CountIterations(5, lte, 5, 10) == 1);


	//			>

	//for (int i = 6; i > 1; i /= 2)
	assert(CountIterations(6, gt, 1, 2) == 2);
	//for (int i = 8; i > 4; i /= 2)
	assert(CountIterations(8, gt, 4, 2) == 1);
	//for (int i = 9; i > 4; i /= 2)
	assert(CountIterations(9, gt, 4, 2) == 1);
	//for (int i = 7; i > 4; i /= 2)
	assert(CountIterations(7, gt, 4, 2) == 1);
	//for (int i = 13; i > 2; i /= 2)
	assert(CountIterations(13, gt, 2, 2) == 3);
	//for (int i = 45; i > 2; i /= 2)
	assert(CountIterations(45, gt, 2, 2) == 4);
	//for (int i = 34; i > 7; i /= 2)
	assert(CountIterations(34, gt, 7, 2) == 3);
	//for (int i = 45; i > 3; i /= 2)
	assert(CountIterations(47, gt, 11, 2) == 2);

	//for (int i = 1234; i > 2; i /= 10)
	assert(CountIterations(1234, gt, 2, 10) == 3);
	//for (int i = 1234; i > 1; i /= 10)
	assert(CountIterations(1234, gt, 1, 10) == 3);
	//for (int i = 999; i > 8; i /= 10)
	assert(CountIterations(999, gt, 8, 10) == 3);
	//for (int i = 999; i > 9; i /= 10)
	assert(CountIterations(999, gt, 9, 10) == 2);
	//for (int i = 38478; i > 37; i /= 10)
	assert(CountIterations(38478, gt, 37, 10) == 4);
	//for (int i = 38478; i > 38; i /= 10)
	assert(CountIterations(38478, gt, 38, 10) == 3);
	//for (int i = 38478; i > 39; i /= 10)
	assert(CountIterations(38478, gt, 39, 10) == 3);

	//			>=

	//for (int i = 13; i >= 2; i /= 2)
	assert(CountIterations(13, gte, 2, 2) == 3);
	//for (int i = 13; i >= 1; i /= 2)
	assert(CountIterations(13, gte, 1, 2) == 4);
	//for (int i = 8; i >= 4; i /= 2)
	assert(CountIterations(8, gte, 4, 2) == 2);
	//for (int i = 9; i >= 4; i /= 2)
	assert(CountIterations(9, gte, 4, 2) == 2);
	//for (int i = 7; i >= 4; i /= 2)
	assert(CountIterations(7, gte, 4, 2) == 1);
	//for (int i = 7; i >= 3; i /= 2)
	assert(CountIterations(7, gte, 3, 2) == 2);
	//for (int i = 37; i >= 5; i /= 2)
	assert(CountIterations(37, gte, 5, 2) == 3);
	//for (int i = 37; i >= 4; i /= 2)
	assert(CountIterations(37, gte, 4, 2) == 4);
	//for (int i = 37; i >= 3; i /= 2)
	assert(CountIterations(37, gte, 3, 2) == 4);
}