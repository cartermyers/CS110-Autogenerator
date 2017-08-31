//--------------------------------------------
//
// Implementation of the SwitchCases subclass
//
//--------------------------------------------

#include "question.h"
#include "SwitchCases.h"
SwitchCases::SwitchCases() : Question()
{
	size = GenerateRand<int>(3, 6); 	//size between 3 and 6 exclusive
	switcher_id = IDENTIFIERS[GenerateRand<int>(0, IDENTIFIERS.size())];
	int range = size * 3 / 2;	//maybe have range as parameter instead

	switcher = GenerateRand<int>(1, range + 1);
	hasDefault = GenerateRand<int>(0, 2) == 1;

	for (int i = 0; i < size; i++)
	{
		//find and insert unique:
		cases.push_back(FindUnique(cases, cases.size(), range));
		caseResults.push_back(FindUnique(caseResults, caseResults.size(), range));

		breaks.push_back(GenerateRand<int>(0, 2) == 1);
	}

	if (hasDefault)
	{
		breaks.push_back(true);
		//find and insert unique once more into caseResults
		caseResults.push_back(FindUnique(caseResults, caseResults.size(), range));
	}
}

SwitchCases::SwitchCases(int swit, vector<int> comparisons, vector<int> results, vector<bool> breakers, bool wantDefault)
	: Question(), switcher(swit), cases(comparisons), caseResults(results), breaks(breakers), hasDefault(wantDefault)
{	
	//make sure it follows proper structure if it has a default
	if (hasDefault)
	{
		assert(cases.size() == caseResults.size() - 1);
	}
	else
	{
		assert(cases.size() == caseResults.size());
	}

	//this should always be true
	assert(breaks.size() == caseResults.size());
	

	size = caseResults.size();
	//never really care about string id so:
	switcher_id = IDENTIFIERS[GenerateRand<int>(0, IDENTIFIERS.size())];
}


//this returns the value of switcher after it has been compared to all cases in a switch case block
int SwitchCases::EvalSwitchCase(vector<int>& wrongAnswers)
{
	//currently support only wrong sizes of 4
	//maybe leave this out and just assign random values to wrong answers > 4
	assert(wrongAnswers.size() >= 4);

	int tempCorrect;	//used to find correct answer
	bool found = false;	//track if we have found a case statement that is true

	for (size_t i = 0; i < cases.size(); i++)
	{
		//found a case
		if (Compare(eq, switcher, cases[i]))
		{
			found = true;
			wrongAnswers[0] = caseResults[i];

			//this simulates a "fall through"
			//go until we find a break statement or until the last statement (including any default)
			while (!breaks[i] && i < (caseResults.size() - 1))
			{
				i++;
			}
			
			wrongAnswers[1] = cases[i % cases.size()];		//may or may not be the same as the original value depending on break statements
			tempCorrect = caseResults[i];
			break;
		}
	}

	//this means we've passed every case except the default one (if there is one)
	if (!found)
	{
		if (hasDefault)
		{
			wrongAnswers[0] = caseResults[caseResults.size() - 2]; //value before the default
			wrongAnswers[1] = cases.back();
			tempCorrect = caseResults.back();
		}
		else
		{
			wrongAnswers[0] = caseResults[GenerateRand<int>(0, caseResults.size())];
			wrongAnswers[1] = cases[0];
			tempCorrect = switcher;
		}
	}

	//generate some common wrong answers (even though they may be same as correct answer)
	wrongAnswers[2] = switcher;
	wrongAnswers[3] = caseResults.back(); //sometimes the default value

	//and check the answers just to be sure
	CheckUniqueAnswers(tempCorrect, wrongAnswers, 0);

	return tempCorrect;
}


void SwitchCases::PrintSwitchCase()
{
	//print the question:
	prompt += "What is the value of " + switcher_id + " after the switch/case block?\n";
	prompt += "<pre>int " + switcher_id + " = " + to_string(switcher) + ";\n";
	prompt += "switch (" + switcher_id + ") {\n";

	//print all the cases (and solve it at the same time?)
	for (size_t i = 0; i < cases.size(); i++)
	{
		prompt += "\tcase " + to_string(cases[i]) + ":\n";
		prompt += "\t\t" + switcher_id + " = " + to_string(caseResults[i]) + ";\n";
		if (breaks[i])
		{
			prompt += "\t\tbreak;\n";
		}
	}

	if (hasDefault)
	{
		prompt += "\tdefault:\n";
		prompt += "\t\t" + switcher_id + " = " + to_string(caseResults.back()) + ";\n"; //since default value is always last one
	}

	prompt += "}</pre>\n";
}

//this function prints the members and solves the question
void SwitchCases::Finish()
{
	//just print right away because the constructor handles all the assignment
	PrintSwitchCase();

	//temp variables to calculate answers
	vector<int> tempWrong(wrong.size(), 0);
	int tempCorrect = EvalSwitchCase(tempWrong);

	CheckUniqueAnswers<int, int>(tempCorrect, tempWrong, 1); //use 1 even though all answers are ints (for some reason 0 precision) doesn't work well; investigate later)

	correct = to_string(tempCorrect);
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = to_string(tempWrong[i]);
	}
}

//random breaks and random default:
void SwitchCases::TypeOne()
{
	Finish();
}


//all breaks and always a default
void SwitchCases::TypeTwo()
{
	//first, explicitly make all cases have a break statement:
	for (size_t i = 0; i < breaks.size(); i++)
	{
		breaks[i] = true;
	}

	//add a default if it wasn't randomly generated by the constructor
	if (!hasDefault)
	{
		hasDefault = true;
		size++;
		breaks.push_back(true);
		//append unique into caseResults
		caseResults.push_back(FindUnique(caseResults, caseResults.size(), caseResults.size() + 3));
	}

	Finish();
}

//no breaks and always a default:
void SwitchCases::TypeThree()
{
	//first, explicitly make all cases have a break statement:
	for (size_t i = 0; i < breaks.size(); i++)
	{
		breaks[i] = false;
	}
	
	//add a default if it wasn't randomly generated by the constructor
	if (!hasDefault)
	{
		hasDefault = true;
		size++;
		breaks.push_back(true);
		//append unique into caseResults
		caseResults.push_back(FindUnique(caseResults, caseResults.size(), caseResults.size() + 3));
	}
	
	Finish();
}

//no breaks and no default:
void SwitchCases::TypeFour()
{
	//first, explicitly make all cases have a break statement:
	for (size_t i = 0; i < breaks.size(); i++)
	{
		breaks[i] = false;
	}
	
	//add a default if it wasn't randomly generated by the constructor
	if (hasDefault)
	{
		hasDefault = false;
		size--;
		breaks.pop_back(); //just remove the last break
		//and the last result:
		caseResults.pop_back();
	}
	
	Finish();
}

void SwitchCases::Tests()
{
	//
	SwitchCases* test;
	vector<int> temp(4, 0); //use this as a parameter to call EvalSwitchCase, but its really of no use
	
	//---------Tests where the switcher has a matching case-----------
	
	//NO DEFAULT:
	//All breaks
	test = new SwitchCases(0, {0, 1, 2, 3}, {4, 5, 6, 7}, {true, true, true, true}, false);
	assert(test->EvalSwitchCase(temp) == 4);
	delete test;
	
	//some breaks
	test = new SwitchCases(0, {0, 1, 2, 3}, {4, 5, 6, 7}, {false, true, false, true}, false);
	assert(test->EvalSwitchCase(temp) == 5);
	delete test;
	
	//some breaks
	test = new SwitchCases(0, {0, 1, 2, 3}, {4, 5, 6, 7}, {true, false, false, true}, false);
	assert(test->EvalSwitchCase(temp) == 4);
	delete test;
	
	//some breaks
	test = new SwitchCases(2, {0, 1, 2, 3}, {4, 5, 6, 7}, {true, true, false, false}, false);
	assert(test->EvalSwitchCase(temp) == 7);
	delete test;
	
	//no breaks
	test = new SwitchCases(0, {0, 1, 2, 3}, {4, 5, 6, 7}, {false, false, false, false}, false);
	assert(test->EvalSwitchCase(temp) == 7);
	delete test;
	
	//WITH DEFAULT
	//all breaks
	test = new SwitchCases(1, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {true, true, true, true, true}, true);
	assert(test->EvalSwitchCase(temp) == 5);
	delete test;
	
	//some breaks
	test = new SwitchCases(3, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {false, true, true, false, true}, true);
	assert(test->EvalSwitchCase(temp) == 8);
	delete test;
	
	//some breaks
	test = new SwitchCases(2, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {false, true, true, false, true}, true);
	assert(test->EvalSwitchCase(temp) == 6);
	delete test;
	
	//no breaks
	test = new SwitchCases(0, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {false, false, false, false, true}, true);
	assert(test->EvalSwitchCase(temp) == 8);
	delete test;
	
	//---------Tests where the switcher has a NO matching case-----------
	
	//WITHOUT DEFAULT
	//all breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7}, {true, true, true, true}, false);
	assert(test->EvalSwitchCase(temp) == 10);
	delete test;
	
	//some breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7}, {true, false, true, false}, false);
	assert(test->EvalSwitchCase(temp) == 10);
	delete test;
	
	//no breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7}, {false, false, false, false}, false);
	assert(test->EvalSwitchCase(temp) == 10);
	delete test;
	
	//WITH DEFAULT
	//all breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {true, true, true, true, true}, true);
	assert(test->EvalSwitchCase(temp) == 8);
	delete test;
	
	//some breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {true, false, false, true, true}, true);
	assert(test->EvalSwitchCase(temp) == 8);
	delete test;
	
	//no breaks
	test = new SwitchCases(10, {0, 1, 2, 3}, {4, 5, 6, 7, 8}, {false, false, false, false, true}, true);
	assert(test->EvalSwitchCase(temp) == 8);
	delete test;
}
