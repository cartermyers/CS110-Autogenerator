#include "Loops.h"

//TODO LOOPS:
//REWRITE EVALUATION FUNCTIONS

//===============================================================================================
//=================================Loops Class and Subclasses===================================
//===============================================================================================

Loops::Loops(int minIters, int maxIters, bool improperLoops) :
		minIterations(minIters), maxIterations(maxIters), allowImproperLoops(improperLoops)
{
	assert(minIterations <= maxIterations);

	//just superficially set all members
	//they should be handled in the InitializeLoop() function
	compSymb = Symbols(-1);
	start = -1;
	stop = -1;
	increment = -1;
	incSymb = Symbols(-1);
}

Loops::Loops(Loops* old)
{
	compSymb = old->GetCompSymb();
	start = old->GetStart();
	stop = old->GetStop();
	increment = old->GetIncrement();
	incSymb = old->GetIncSymb();
}

//implement these two functions here because they are almost the same for every class
//except do while
vector<int> Loops::ShowIterations()
{
	vector<int> res;

	int tempStart = start;

	while (Operation<bool>(compSymb, tempStart, stop))
	{
		res.push_back(tempStart);
		tempStart = Operation<int>(incSymb, tempStart, increment);
	}

	return res;
}

vector<int> Loops::ShowLoop()
{
	ComputeLoop(); //so we count the number of iterations and then change them to be between minIterations and maxIterations

	return ShowIterations();
}

void Loops::SetLoopParameters(bool improperLoops, int minIters, int maxIters)
{
	allowImproperLoops = improperLoops;

	if (minIters != -1)
	{
		minIterations = minIters;
	}

	if (maxIters != -1)
	{
		maxIterations = maxIters;
	}
}


void Loops::InitializeLoop(Symbols minCompSymb, Symbols maxCompSymb, Symbols minIncSymb, Symbols maxIncSymb)
{
	assert(minCompSymb <= maxCompSymb);
	assert(minIncSymb <= maxIncSymb);

	//generate the comparison operator (e.g. "<", ">", "<=")
	compSymb = GenerateRand<Symbols>(minCompSymb, maxCompSymb);

	//generate the increment operator (e.g. "+=", "*=")
	incSymb = GenerateRand<Symbols>(minIncSymb, maxIncSymb);

	int max = GenerateRand<int>(5, 9);

	//set increment
	switch (rand() % 3)
	{
	case 0:
		if (incSymb == add || incSymb == sub)
		{
			increment = 1;
		}
		else
		{
			increment = 2;
		}
		break;
	case 1:
		increment = 5;
		//only use 5 as the increment step for "+" and "-"
		if (incSymb == add || incSymb == sub)
		{
			break;
		}
	case 2:
		increment = 10;
		break;
	}

	//generate the start and the stop assuming that it's a lt '<' sign
	switch (incSymb)
	{
	case add:
	case sub:
		start = increment * (2 + rand() % max);
		stop = start + (increment * GenerateRand<int>(minIterations, maxIterations)); //roughly give the right amount of iterations
		//make the stop look less nice:
		stop += GenerateRand<int>(0, increment - 1);
		break;
	case mul:
	case divide:
		start = 1 + rand() % 4;
		stop = int(start * pow(increment, GenerateRand<int>(minIterations, maxIterations))); //roughly give the right amount of iterations
		//and add this random end to make it look "less nice"
		//and it may add another loop or two
		stop += rand() % increment;
		break;
	}


	//and make sure we have the proper increment direction for the comparison operator
	//(e.g. i > 5 if i-- and i <= 3 means i++ etc.)
	//read "if compSymb is > or >= then incSymb is -= or -= (and swap)
	//or if compSymb is < or <= then incSymb is += or -= (and dont swap)"

	if ((compSymb == gt || compSymb == gte))
	{
		int temp = start;
		start = stop;
		stop = temp;

		if (!allowImproperLoops || Operation<bool>(neq, GenerateRand<int>(0, 3), 0))
		{
			if (incSymb == add)
			{
				incSymb = sub;
			}
			else if (incSymb == mul)
			{
				incSymb = divide;
			}
		}
	}
	//but if we allow improper loops, do a swap at random.
	// this may seem weird here, but it is to make infinite loops happen with ALL operators.
	// this condition isn't necessary to the effectiveness of the question,
	// but if it wasnt included, no < or <= operators would have infinite loops
	else if (!allowImproperLoops || Operation<bool>(neq, GenerateRand<int>(0, 3), 0))
	{
		if (incSymb == sub)
		{
			incSymb = add;
		}
		else if (incSymb == divide)
		{
			incSymb = mul;
		}
	}
}

// -1 means a loop that "never" terminantes
int Loops::ComputeLoop()
{
	int res = CountIterations();

	assert(allowImproperLoops || res != -1);

	if (res != -1 && (res < minIterations || res > maxIterations))
	{
		int estIterations = (maxIterations + minIterations) / 2; //roughly how many iterations we want (in the middle)

		int diff; //this is the scaled version of the difference

		if (incSymb == add || incSymb == sub)
		{
			diff = estIterations * increment;
		}
		else
		{
			diff = int(pow(increment, estIterations));  //the difference needed for that many iterations
		}

		//now update the stop to have a proper condition (dependent on the incSymb)
		stop = Operation<int>(incSymb, start, diff);

		if (stop <= 0)
		{
			if (incSymb == add || incSymb == sub)
			{
				start -= stop;
				stop = 0;
			}
			else
			{
				start = diff;
				stop = 1;
			}
		}
		res = CountIterations();
	}

	return res;
}

int Loops::CountIterations()
{
	//first, check for "improper" loops
	//read "if compSymb is > or >= and incSymb is += or *=
	// or if compSymb is < or <= and incSymb is -= or /=
	// then return -1 if the comparison is true (i.e. it generates an "infinite" loop)
	if ((compSymb == gt || compSymb == gte) && (incSymb == add || incSymb == mul))
	{
		if (Operation<bool>(compSymb, start, stop))
		{
			return -1;
		}
	}
	else if ((compSymb == lt || compSymb == lte) && (incSymb == sub || incSymb == divide))
	{
		if (Operation<bool>(compSymb, start, stop))
		{
				return -1;
		}
	}

	//here is the actual counting of loops

	int tempStart = start;
	int res = 0;

	while (Operation<bool>(compSymb, tempStart, stop))
	{
		res += 1;
		tempStart = Operation<int>(incSymb, tempStart, increment);
	}

	return res;
}

//===============================================================================================
//=============================================Tests=============================================
//===============================================================================================

void Loops::Tests()
{
	/*
			PART ONE
		Here are loops only using + and - increments

	*/

	//			< and +=

	compSymb = lt;
	incSymb = add;

	//for (int i = 0; i < 5; i += 1)
	start = 0; stop = 5; increment = 1;
	assert(CountIterations() == 5);

	//for (int i = 0; i < 5; i += 2)
	start = 0; stop = 5; increment = 2;
	assert(CountIterations() == 3);

	//for (int i = 0; i < 6; i += 2)
	start = 0; stop = 6; increment = 2;
	assert(CountIterations() == 3);

	//for (int i = 0; i < 0; i += 1)
	start = 0; stop = 0; increment = 1;
	assert(CountIterations() == 0);




	//			<= and +=

	compSymb = lte;
	incSymb = add;

	//for (int i = 0; i <= 0; i += 1)
	start = 0; stop = 0; increment = 1;
	assert(CountIterations() == 1);

	//for (int i = 0; i <= 5; i += 1)
	start = 0; stop = 5; increment = 1;
	assert(CountIterations() == 6);

	//for (int i = 0; i <= 6; i += 2)
	start = 0; stop = 6; increment = 2;
	assert(CountIterations() == 4);

	//for (int i = 0; i <= 5; i += 2)
	start = 0; stop = 5; increment = 2;
	assert(CountIterations() == 3);



	//			> and -=

	compSymb = gt;
	incSymb = sub;

	//for (int i = 4; i > 0; i -= 1)
	start = 4; stop = 0; increment = 1;
	assert(CountIterations() == 4);

	//for (int i = 4; i > 0; i -= 2)
	start = 4; stop = 0; increment = 2;
	assert(CountIterations() == 2);

	//for (int i = 3; i > 0; i -= 2)
	start = 3; stop = 0; increment = 2;
	assert(CountIterations() == 2);

	//for (int i = 0; i > 0; i -= 2)
	start = 0; stop = 0; increment = 2;
	assert(CountIterations() == 0);

	//			>= and -=

	compSymb = gte;
	incSymb = sub;

	//for (int i = 0; i >= 0; i -= 1)
	start = 0; stop = 0; increment = 1;
	assert(CountIterations() == 1);

	//for (int i = 3; i >= 1; i -= 1)
	start = 3; stop = 1; increment = 1;
	assert(CountIterations() == 3);

	//for (int i = 6; i >= 1; i -= 2)
	start = 6; stop = 1; increment = 2;
	assert(CountIterations() == 3);

	//for (int i = 6; i >= 0; i -= 2)
	start = 6; stop = 0; increment = 2;
	assert(CountIterations() == 4);



	//		PART TWO
	//	Here, increments with * and / are tested

	//right now, I'm only adding test cases for *= 2 and /= 10 and all those combinations
	//but if we wish to use different increment amounts in the future, it's a good idea to add more test cases

	// 			< and *= 2

	compSymb = lt;
	incSymb = mul;
	increment = 2;

	//for (int i = 1; i < 8; i *= 2)
	start = 1; stop = 8;
	assert(CountIterations() == 3);

	//for (int i = 2; i < 8; i *= 2)
	start = 2; stop = 8;
	assert(CountIterations() == 2);

	//for (int i = 3; i < 8; i *= 2)
	start = 3; stop = 8;
	assert(CountIterations() == 2);

	//for (int i = 1; i < 9; i *= 2)
	start = 1; stop = 9;
	assert(CountIterations() == 4);

	//for (int i = 1; i < 7; i *= 2)
	start = 1; stop = 7;
	assert(CountIterations() == 3);

	//for (int i = 1; i < 5; i *= 2)
	start = 1; stop = 5;
	assert(CountIterations() == 3);

	//for (int i = 5; i < 19; i *= 2)
	start = 5; stop = 19;
	assert(CountIterations() == 2);


	//now < and *= 10

	increment = 10;

	//for (int i = 2; i < 18; i *= 10)
	start = 2; stop = 18;
	assert(CountIterations() == 1);

	//for (int i = 3; i < 3578; i *= 10)
	start = 3; stop = 3578;
	assert(CountIterations() == 4);

	//for (int i = 3; i < 3000; i *= 10)
	start = 3; stop = 3000;
	assert(CountIterations() == 3);

	//for (int i = 3; i < 3001; i *= 10)
	start = 3; stop = 3001;
	assert(CountIterations() == 4);


	//			<= and *= 2

	compSymb = lte;
	incSymb = mul;
	increment = 2;

	//for (int i = 1; i <= 8; i *= 2)
	start = 1; stop = 8;
	assert(CountIterations() == 4);

	//for (int i = 1; i <= 9; i *= 2)
	start = 1; stop = 9;
	assert(CountIterations() == 4);

	//for (int i = 1; i <= 7; i *= 2)
	start = 1; stop = 7;
	assert(CountIterations() == 3);

	//for (int i = 2; i <= 8; i *= 2)
	start = 2; stop = 8;
	assert(CountIterations() == 3);

	//for (int i = 6; i <= 48; i *= 2)
	start = 6; stop = 48;
	assert(CountIterations() == 4);

	//for (int i = 6; i <= 47; i *= 2)
	start = 6; stop = 47;
	assert(CountIterations() == 3);

	//for (int i = 1; i <= 1; i *= 2)
	start = 1; stop = 1;
	assert(CountIterations() == 1);


	//now <= with *= 10

	increment = 10;

	//for (int i = 3; i <= 3000; i *= 10)
	start = 3; stop = 3000;
	assert(CountIterations() == 4);

	//for (int i = 3; i <= 3001; i *= 10)
	start = 3; stop = 3001;
	assert(CountIterations() == 4);

	//for (int i = 4; i <= 476; i *= 10)
	start = 4; stop = 476;
	assert(CountIterations() == 3);

	//for (int i = 5; i <= 5; i *= 10)
	start = 5; stop = 5;
	assert(CountIterations() == 1);


	//			> with /= 2

	compSymb = gt;
	incSymb = divide;
	increment = 2;

	//for (int i = 6; i > 1; i /= 2)
	start = 6; stop = 1;
	assert(CountIterations() == 2);

	//for (int i = 8; i > 4; i /= 2)
	start = 8; stop = 4;
	assert(CountIterations() == 1);

	//for (int i = 9; i > 4; i /= 2)
	start = 9; stop = 4;
	assert(CountIterations() == 1);

	//for (int i = 7; i > 4; i /= 2)
	start = 7; stop = 4;
	assert(CountIterations() == 1);

	//for (int i = 13; i > 2; i /= 2)
	start = 13; stop = 2;
	assert(CountIterations() == 3);

	//for (int i = 45; i > 2; i /= 2)
	start = 45; stop = 2;
	assert(CountIterations() == 4);

	//for (int i = 34; i > 7; i /= 2)
	start = 34; stop = 7;
	assert(CountIterations() == 3);

	//for (int i = 45; i > 3; i /= 2)
	start = 45; stop = 3;
	assert(CountIterations() == 4);


	//now /= 10
	increment = 10;

	//for (int i = 1234; i > 2; i /= 10)
	start = 1234; stop = 2;
	assert(CountIterations() == 3);

	//for (int i = 1234; i > 1; i /= 10)
	start = 1234; stop = 1;
	assert(CountIterations() == 3);

	//for (int i = 999; i > 8; i /= 10)
	start = 999; stop = 8;
	assert(CountIterations() == 3);

	//for (int i = 999; i > 9; i /= 10)
	start = 999; stop = 9;
	assert(CountIterations() == 2);

	//for (int i = 38478; i > 37; i /= 10)
	start = 38478; stop = 37;
	assert(CountIterations() == 4);

	//for (int i = 38478; i > 38; i /= 10)
	start = 38478; stop = 38;
	assert(CountIterations() == 3);

	//for (int i = 38478; i > 39; i /= 10)
	start = 38478; stop = 39;
	assert(CountIterations() == 3);


	//			>= with /= 2

	compSymb = gte;
	incSymb = divide;
	increment = 2;

	//for (int i = 13; i >= 2; i /= 2)
	start = 13; stop = 2;
	assert(CountIterations() == 3);

	//for (int i = 13; i >= 1; i /= 2)
	start = 13; stop = 1;
	assert(CountIterations() == 4);

	//for (int i = 8; i >= 4; i /= 2)
	start = 8; stop = 4;
	assert(CountIterations() == 2);

	//for (int i = 9; i >= 4; i /= 2)
	start = 9; stop = 4;
	assert(CountIterations() == 2);

	//for (int i = 7; i >= 4; i /= 2)
	start = 7; stop = 4;
	assert(CountIterations() == 1);

	//for (int i = 7; i >= 3; i /= 2)
	start = 7; stop = 3;
	assert(CountIterations() == 2);

	//for (int i = 37; i >= 5; i /= 2)
	start = 37; stop = 5;
	assert(CountIterations() == 3);

	//for (int i = 37; i >= 4; i /= 2)
	start = 37; stop = 4;
	assert(CountIterations() == 4);

	//for (int i = 37; i >= 3; i /= 2)
	start = 37; stop = 3;
	assert(CountIterations() == 4);



	//		PART THREE
	// Here, all improper loops are tested

	// with <

	compSymb = lt;
	increment = 2;

	//for (int i = 1; i < 10; i -= 2)
	start = 1; stop = 10; incSymb = sub;
	assert(CountIterations() == -1);

	//for (int i = 1; i < 10; i /= 2)
	start = 1; stop = 10; incSymb = divide;
	assert(CountIterations() == -1);

	// with >
	compSymb = gt;
	increment = 2;

	//for (int i = 10; i > 1; i += 2)
	start = 10; stop = 1; incSymb = add;
	assert(CountIterations() == -1);

	//for (int i = 10; i > 1; i *= 2)
	start = 10; stop = 1; incSymb = mul;
	assert(CountIterations() == -1);
}
