//*******************************************************************************************
//							LOOPS SUBCLASS DEFINITIONS
//
//							based off of For Loop w Skew
//*******************************************************************************************

#include "QLoops.h"

QLoops::QLoops(int loop, int questionType) : Question()
{
	loopType = loop;
	type = questionType;

	switch (loopType)
	{
	case 0: //for loops
		currentLoop = new ForLoops();
		break;
	case 1: //while loops
		currentLoop = new WhileLoops();
		break;
	case 2:	//do while loops
		currentLoop = new DoLoops();
		break;
	default:
		currentLoop = new ForLoops();
		break;
	}
}

QLoops::~QLoops()
{
	delete currentLoop;
	currentLoop = NULL;
}

void QLoops::TypeOne()
{
	//these functions make and ouput the questions:
	switch (type)
	{
		case 0: //count a single loop
			currentLoop->SetLoopParameters(false, 3, 6);
			currentLoop->InitializeLoop(lt, lt, add, add);
			SingleLoopCount();
			break;
		case 1: //prints out the counter at each step
			currentLoop->SetLoopParameters(false, 2, 3);
			currentLoop->InitializeLoop(lt, lt, add, add);
			SingleLoopPrint();
			break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
}

void QLoops::TypeTwo()
{
	//these functions make and ouput the questions:
	switch (type)
	{
	case 0: //count a single loop
		currentLoop->SetLoopParameters(true, 3, 6);
		currentLoop->InitializeLoop(gt, lte, add, sub);
		SingleLoopCount();
		break;
	case 1: //prints out the counter at each step
		currentLoop->SetLoopParameters(false, 3, 4);
		currentLoop->InitializeLoop(gt, lte, add, sub);
		SingleLoopPrint();
		break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
}

void QLoops::TypeThree()
{
	//these functions make and ouput the questions:
	switch (type)
	{
	case 0: //count a single loop
		currentLoop->SetLoopParameters(true, 2, 4);
		currentLoop->InitializeLoop(gt, lte, mul, divide);
		SingleLoopCount();
		break;
	case 1: //prints out the counter at each step
		currentLoop->SetLoopParameters(false, 2, 3);
		currentLoop->InitializeLoop(gt, lte, mul, divide);
		SingleLoopPrint();
		break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
}

void QLoops::TypeFour()
{
	Loops* innerLoop;

	//initialize inner loop to same type as outer loop:
	switch (loopType)
	{
	case 0: //for loops
		innerLoop = new ForLoops();
		break;
	case 1: //while loops
		innerLoop = new WhileLoops();
		break;
	case 2:	//do while loops
		innerLoop = new DoLoops();
		break;
	default:
		innerLoop = new ForLoops();
		break;
	}

	//this question is only for nested loops
	switch (type)
	{
	case 0: //count a nested loop
		currentLoop->SetLoopParameters(false, 2, 4);
		currentLoop->InitializeLoop(gt, lte, add, sub);

		innerLoop->SetLoopParameters(false, 2, 4);
		innerLoop->InitializeLoop(gt, lte, add, sub);

		NestedLoopCount(innerLoop);
		break;
	case 1: //prints out the counter at each step
		break;
		/*
		currentLoop->SetLoopParameters(false, 3, 5);
		currentLoop->InitializeLoop(gt, lte, add, sub);
		SingleLoopPrint();
		break;
		*/
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}

	delete innerLoop;
	innerLoop = NULL;
}

void QLoops::SingleLoopCount()
{
	prompt += "How many times does the \'*\' print?\n";

	//make an answer based on difficulty parameters:
	int tempCorrect = currentLoop->ComputeLoop();
	vector<int> tempWrong(wrong.size(), 0);

	//make some low-effort wrong answers:
	tempWrong[0] = abs(tempCorrect - 1);
	tempWrong[1] = tempCorrect + 1;

	tempWrong[2] = abs(Operation<int>(GenerateRand<Symbols>(add, sub), tempCorrect, GenerateRand<int>(2, 4)));
	tempWrong[3] = abs(Operation<int>(GenerateRand<Symbols>(add, sub), tempCorrect, GenerateRand<int>(2, 4)));

	//check answers and then get them ready to print
	CheckUniqueAnswers(tempCorrect, tempWrong);

	correct = to_string(tempCorrect);

	if (currentLoop->GetAllowImproperLoops())
	{
		if (tempCorrect == -1)
		{
			correct = "Around a couple billion";
		}
		else
		{
			wrong[3] = "Around a couple billion";
			tempWrong.pop_back();	//remove the last wrong answer from being copied for printing
		}
	}

	//assert(wrong.size() == tempWrong.size());
	for (size_t i = 0; i < tempWrong.size(); i++)
	{
		wrong[i] = to_string(tempWrong[i]);
	}

	//lastly, print the loop
	prompt += "<pre>";
	prompt += currentLoop->Print(ALPHA_LETTERS[GenerateRand<int>(0, ALPHA_LETTERS.size() - 1)], "cout << \'*\';");
	prompt += "</pre>";
}

void QLoops::NestedLoopCount(Loops* innerLoop)
{
	prompt += "How many times does the \'*\' print?\n";

	//now make a nested for loop:
	int tempCorrect = currentLoop->ComputeLoop();
	vector<int> tempWrong(wrong.size(), 0);

	tempWrong[0] = tempCorrect + 1;
	tempWrong[1] = tempCorrect;

	tempCorrect *= innerLoop->ComputeLoop();

	tempWrong[2] = tempWrong[0] * tempWrong[1];
	tempWrong[3] = tempWrong[0] * (tempWrong[1] + 1);

	//check answers and then get them ready to print
	CheckUniqueAnswers(tempCorrect, tempWrong);

	correct = to_string(tempCorrect);

	if (currentLoop->GetAllowImproperLoops())
	{
		if (tempCorrect == -1)
		{
			correct = "Around a couple billion";
		}
		else
		{
			wrong[3] = "Around a couple billion";
			tempWrong.pop_back();	//remove the last wrong answer from being copied for printing
		}
	}

	//assert(wrong.size() == tempWrong.size());
	for (size_t i = 0; i < tempWrong.size(); i++)
	{
		wrong[i] = to_string(tempWrong[i]);
	}

	//print the loop:
	prompt += "<pre>";
	prompt += currentLoop->Print("i", innerLoop->Print("j", "cout << \'*\';"));
	prompt += "</pre>";
}

void QLoops::SingleLoopPrint()
{
	//no infinite loops for this one:
	assert(!(currentLoop->GetAllowImproperLoops()));

	string id = ALPHA_LETTERS[rand() % ALPHA_LETTERS.size()]; //the id

	prompt += "What is the following output of the code?\n<pre>";

	//make an answer based on difficulty parameters:
	vector<int> tempCorrect = currentLoop->ShowLoop();
	vector< vector<int> > tempWrong(wrong.size());

	//print the loop
	prompt += currentLoop->Print(id, "cout << " + id + " << \' \';") + "</pre>";

	for (size_t i = 0; i < tempCorrect.size(); i++)
	{
		tempWrong[1].push_back(Operation<int>(currentLoop->GetIncSymb(), tempCorrect[i], currentLoop->GetIncrement()));
		//just a random array:
		tempWrong[3].push_back(tempCorrect[i]);
	}

	tempWrong[3].push_back(Operation<int>(currentLoop->GetIncSymb(), tempCorrect.back(), currentLoop->GetIncrement()));

	//and make some off by one errors:
	for (size_t i = 0; i < tempCorrect.size() - 1; i++)
	{
		tempWrong[0].push_back(tempCorrect[i + 1]);
		tempWrong[2].push_back(tempCorrect[i]);
	}

	CheckAndPrintAnswers(tempCorrect, tempWrong);
}

void QLoops::CheckAndPrintAnswers(const vector<int>& tempCorrect, vector< vector<int> >& tempWrong)
{
	CheckUniqueAnswers(tempCorrect, tempWrong);

	//format answers for printing:
	for (size_t i = 0; i < tempCorrect.size(); i++)
	{
		correct += to_string(tempCorrect[i]) + " ";
	}

	assert(wrong.size() == tempWrong.size());
	for (size_t i = 0; i < tempWrong.size(); i++)
	{
		for (size_t j = 0; j < tempWrong[i].size(); j++)
		{
			wrong[i] += to_string(tempWrong[i][j]) + " ";
		}
	}
}

//===============================================================================================
//================================================ Tests ========================================
//===============================================================================================

void QLoops::Tests()
{
	//Right now, these first two tests just call the virtual functions in their immediate superclass
	Loops* tester = new ForLoops();
	tester->Loops::Tests();

	tester->Tests();
	delete tester;

	tester = new DoLoops();
	tester->Tests();
	delete tester;

	tester = new WhileLoops();
	tester->Tests();
	delete tester;
}
