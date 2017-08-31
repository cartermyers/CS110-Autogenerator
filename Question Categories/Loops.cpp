//*******************************************************************************************
//							LOOPS SUBCLASS DEFINITIONS	
//
//							based off of For Loop w Skew
//*******************************************************************************************

#include "Loops.h"

void Loops::TypeOne()
{
	int type = 1;	//modify this to change the type of question that is calculated
					//this is used in the switch case below
	QLoops* current;
		
	//maybe there could be an if else statement here with a flag
	//indicating if the question should use linear or exponential loops
	switch (category)
	{
		case 0: //for loops
			current = new LinearForLoops();
			break;
		case 1: //while loops
			current = new LinearWhileLoops();
			break;
		case 2:	//do while loops
			current = new LinearDoLoops();
			break;
		default:
			current = new LinearForLoops();
			break;
	}

	//these functions make and ouput the questions:
	switch (type)
	{
		case 0: //count a single loop
			SingleLoopCount(current, 2, 8);
			break;
		case 1: //prints out the counter at each step
			SingleLoopPrint(current, 3, 5);
			break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
	
	delete current;
}

void Loops::TypeTwo()
{
	int type = 1;	//modify this to change the type of question that is calculated
					//this is used in the switch case below
	QLoops* current;
		
	switch (category)
	{
		case 0: //for loops
			current = new ExpForLoops();
			break;
		case 1: //while loops
			current = new ExpWhileLoops();
			break;
		case 2:	//do while loops
			current = new ExpDoLoops();
			break;
		default: //should never happen
			current = new ExpForLoops();
	}

	//these functions make and ouput the questions:
	switch (type)
	{
		case 0: //count a single loop
			SingleLoopCount(current, 1, 5);
			break;
		case 1: //prints out the counter at each step
			SingleLoopPrint(current, 3, 5);
			break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
	
	delete current;
}

void Loops::TypeThree()
{
	int type = 0;	//modify this to change the type of question that is calculated
					//this is used in the switch case below
	QLoops* current;
		
	switch (category)
	{
		case 0: //for loops
			current = new LinearForLoops();
			break;
		case 1: //while loops
			current = new LinearWhileLoops();
			break;
		case 2:	//do while loops
			current = new LinearDoLoops();
			break;
		default:
			current = new LinearForLoops();
			break;
	}

	//these functions make and ouput the questions:
	//NOTE: only type == 0 is supported right now
	switch (type)
	{
		case 0: //count a single loop
			NestedLoopCount(current, 2, 5);
			break;
		//case 1: //prints out the counter at each step
			//SingleLoopPrint(current, 3, 5);
			//break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
	
	delete current;
}

void Loops::TypeFour()
{
	int type = 0;	//modify this to change the type of question that is calculated
					//this is used in the switch case below
	QLoops* current;
		
	switch (category)
	{
		case 0: //for loops
			current = new ExpForLoops();
			break;
		case 1: //while loops
			current = new ExpWhileLoops();
			break;
		case 2:	//do while loops
			current = new ExpDoLoops();
			break;
		default: //should never happen
			current = new ExpForLoops();
	}

	//these functions make and ouput the questions:
	//NOTE: only type == 0 is supported
	switch (type)
	{
		case 0: //count a nested loop
			NestedLoopCount(current, 1, 4);
			break;
		//case 1: //prints out the counter at each step
			//SingleLoopPrint(current, 3, 5);
			//break;
		//maybe make this a function in the future?
		//SingleLoopTerminatingValue() or something?
	}
	
	delete current;
}

void Loops::SingleLoopCount(QLoops* current, int minIterations, int maxIterations)
{	
	prompt += "How many times does the \'*\' print?\n";

	//initialize parameters:
	current->InitializeLoop();

	//make an answer based on difficulty parameters:
	int tempCorrect = current->ComputeLoop(minIterations, maxIterations);
	vector<int> tempWrong(wrong.size(), 0);
	
	//make some low-effort wrong answers:
	tempWrong[0] = tempCorrect - 1;
	tempWrong[1] = tempCorrect + 1;
	
	tempWrong[2] = Question::Arithmetic<int>(GenerateRand<Symbols>(add, sub + 1), tempCorrect, GenerateRand<int>(2, 5));
	tempWrong[3] = Question::Arithmetic<int>(GenerateRand<Symbols>(add, sub + 1), tempCorrect, GenerateRand<int>(2, 5));
	
	CheckAndPrintAnswers(tempCorrect, tempWrong);
	
	//lastly, print the loop
	prompt += "<pre>";
	prompt += current->PrintLoop(current, ALPHA_LETTERS[rand() % ALPHA_LETTERS.size()], "\'*\'");
	prompt += "</pre>";
}

void Loops::NestedLoopCount(QLoops* current, int minIterations, int maxIterations)
{
	prompt += "How many times does the \'*\' print?\n";

	//initialize parameters:
	current->InitializeLoop();

	//now make a nested for loop:
	int tempCorrect = current->ComputeLoop(minIterations, maxIterations);
	vector<int> tempWrong(wrong.size(), 0);

	tempWrong[0] = tempCorrect + 1;
	tempWrong[1] = tempCorrect;

	//save the current data of the outer loop (so we can print later)
	//NOTE: since we only need the data members of the loop,
	//we can initalize it as any subclass of QLoops.
	//This may be considered bad practice, but it's the only way I could get it to work without
	//forcing the Type() functions that call this function to either be fixed as single or nested.
	//What I am basically saying, is that this allows more flexability in the calling class 
	//to create different types of questions
	QLoops* outer = new LinearForLoops(current);
	
	//Reset the parameters:
	current->InitializeLoop();

	tempCorrect *= current->ComputeLoop(minIterations, maxIterations);

	tempWrong[2] = tempWrong[0] * tempWrong[1];
	tempWrong[3] = tempWrong[0] * (tempWrong[1] + 1);
	
	CheckAndPrintAnswers(tempCorrect, tempWrong);
	
	//print the loop:
	prompt += "<pre>";
	prompt += current->PrintLoop(outer, "i", current, "j", "\'*\'");
	prompt += "</pre>";
}

void Loops::SingleLoopPrint(QLoops* current, int minIterations, int maxIterations)
{
	string id = ALPHA_LETTERS[rand() % ALPHA_LETTERS.size()]; //the id

	prompt += "What is the following output of the code?\n<pre>";

	//initialize parameters:
	current->InitializeLoop();

	//make an answer based on difficulty parameters:
	vector<int> tempCorrect = current->ShowLoop(minIterations, maxIterations);
	vector< vector<int> > tempWrong(wrong.size());
	
	//print the loop
	prompt += current->PrintLoop(current, id, id) + "</pre>";

	for (size_t i = 0; i < tempCorrect.size(); i++)
	{
		tempWrong[1].push_back(Question::Arithmetic<int>(current->GetIncSymb(), tempCorrect[i], current->GetIncrement()));
		//just a random array:
		tempWrong[3].push_back(tempCorrect[i]);
	}

	tempWrong[3].push_back(Question::Arithmetic<int>(current->GetIncSymb(), tempCorrect.back(), current->GetIncrement()));
	
	//and make some off by one errors:
	for (size_t i = 0; i < tempCorrect.size() - 1; i++)
	{
		tempWrong[0].push_back(tempCorrect[i + 1]);
		tempWrong[2].push_back(tempCorrect[i]);
	}
	
	CheckAndPrintAnswers(tempCorrect, tempWrong);
}

void Loops::CheckAndPrintAnswers(const vector<int>& tempCorrect, vector< vector<int> >& tempWrong)
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

void Loops::CheckAndPrintAnswers(const int& tempCorrect, vector<int>& tempWrong)
{	
	CheckUniqueAnswers(tempCorrect, tempWrong);

	//format answers for printing:
	correct = to_string(tempCorrect);

	//assert(wrong.size() == tempWrong.size());
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = to_string(tempWrong[i]);
	}
}

//===============================================================================================
//================================================ Tests ========================================
//===============================================================================================

void Loops::Tests()
{
	//Right now, these first two tests just call the virtual functions in their immediate superclass
	QLoops* tester = new LinearForLoops();
	tester->Tests();
	delete tester;
	
	tester = new ExpForLoops();
	tester->Tests();
	delete tester;
		
	//call do loops tests because they have some special cases
	//Only include these if you are using DoLoops
	tester = new LinearDoLoops();
	tester->Tests();
	delete tester;
	
	tester = new ExpDoLoops();
	tester->Tests();
	delete tester;
}