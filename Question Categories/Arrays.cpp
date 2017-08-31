
#include "question.h"
#include "Arrays.h"

//*******************************************************************************************
//							ARRAYS SUBCLASS DEFINITIONS	
//
//*******************************************************************************************

//--------------------------------------------
// Difficulty One:
// Element swap and Access
//--------------------------------------------
void Arrays::TypeOne()
{
	int id = GenerateRand<int>(0, IDENTIFIERS.size()); 	//pick a random array identifier
	int size = GenerateRand<int>(4, 7); 				//pick a random array size (from 4 - 6 inclusive)

	vector<int> tempCorrect(size, 0);
	vector<vector<int>> tempWrong(wrong.size());

	prompt += "What are the contents of the array after the following statements?\n";
	prompt += "<pre>";
	prompt += "int " + IDENTIFIERS[id] + "[" + to_string(size) + "] = \\{";

	//create a random original array and print it at the same time:
	for (int i = 0; i < size; i++)
	{
		//insert a new value into the array based on what's already initialized
		//so each array is unique (this may be a little lame based on expectations)
		tempCorrect[i] = FindUnique(tempCorrect, i, 10);
		
		prompt += to_string(tempCorrect[i]) + ", ";
		
		for (size_t j = 0; j < tempWrong.size(); j++)
		{
			tempWrong[j].push_back(tempCorrect[i]);
		}
	}

	//cut off the last ", " and add a "}":
	prompt.replace(prompt.end() - 2, prompt.end(), "\\};\n");

	//perform the swap:
	int index1 = GenerateRand<int>(0, size);
	int index2;
	//with two different elements
	do
	{
		index2 = GenerateRand<int>(0, size);
	} while (index2 == index1);

	prompt += "int temp;\n";
	prompt += "temp = " + IDENTIFIERS[id] + "[" + to_string(index1) + "];\n";
	prompt += IDENTIFIERS[id] + "[" + to_string(index1) + "] = " + IDENTIFIERS[id] + "[" + to_string(index2) + "];\n";
	prompt += IDENTIFIERS[id] + "[" + to_string(index2) + "] = temp;";
	prompt += "</pre>\n";

	//do an off-by-one error:
	tempWrong[2][abs(index2 - 1)] = tempCorrect[abs(index1 - 1)];
	tempWrong[2][abs(index1 - 1)] = tempCorrect[abs(index2 - 1)];
	//opposite off-by-one error:
	tempWrong[3][(index2 + 1) % size] = tempCorrect[(index1 + 1) % size];
	tempWrong[3][(index1 + 1) % size] = tempCorrect[(index2 + 1) % size];

	tempWrong[1][abs(index2 - 1)] = tempCorrect[abs(index1 - 1)];
	tempWrong[1][(index1 + 1) % size] = tempCorrect[(index2 + 1) % size];

	//this is basically the answer-generating function
	//since it's so simple, I don't think there's any need to test it directly.
	//Just examine the outputs and make sure the question makes sense
	int temp = tempCorrect[index1];
	tempCorrect[index1] = tempCorrect[index2];
	tempCorrect[index2] = temp;

	//check the four wrong arrays
	CheckUniqueAnswers(tempCorrect, tempWrong);

	correct += "\\{";
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] += "\\{";
	}

	//get the answers ready for printing:
	for (int j = 0; j < size; j++)
	{
		correct += to_string(tempCorrect[j]) + ", ";

		for (size_t i = 0; i < wrong.size(); i++)
		{
			wrong[i] += to_string(tempWrong[i][j]) + ", ";
		}
	}

	correct.replace(correct.end() - 2, correct.end(), "\\}");
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i].replace(wrong[i].end() - 2, wrong[i].end(), "\\}");
	}
}


//-----------------------------------------------------
// Difficulty Two:
// Simple Array Traversal
//-------------------------------------------------------
void Arrays::TypeTwo()
{
	int size = GenerateRand<int>(3, 7); //size of the array between 3 and 6
	int base = 0;						//use simple numbers here for an easy question
	int increment = 1;

	int offsets[3] = { 1, 5, 10 };

	int offset = offsets[GenerateRand<int>(0, 3)];

	int id = GenerateRand<int>(0, IDENTIFIERS.size());

	vector<int> tempCorrect(size, 0);
	vector< vector<int> > tempWrong(wrong.size());

	prompt += "What are the contents of the array after the following?\n";
	prompt += "<pre>";
	prompt += "int " + IDENTIFIERS[id] + "[" + to_string(size) + "] = \\{";

	//create a random original array and print it at the same time:
	for (size_t i = 0; i < tempCorrect.size(); i++)
	{
		tempCorrect[i] = GenerateRand<int>(0, 11);
		prompt += to_string(tempCorrect[i]) + ", ";
		//initialize the wrong answers while we're at it
		for (size_t j = 0; j < tempWrong.size(); j++)
		{
			tempWrong[j].push_back(tempCorrect[i]);
		}
	}

	prompt.replace(prompt.end() - 2, prompt.end(), "\\};\n");

	prompt += "for (int i = " + to_string(base) + "; i < " + to_string(size) + "; i += " + to_string(increment) + ")\n";
	prompt += "\t\\{ " + IDENTIFIERS[id] + "[i] += " + to_string(offset) + "; \\}";		//add two \\ so only one \ prints
	prompt += "</pre>\n";

	int current = 0;
	for (int i = base; i < size; i += increment)
	{
		//just to double check:
		assert(size_t(current) < tempCorrect.size());
		
		//store at [length] because length starts at 0 and gives the exact size declared
		tempCorrect[current] += offset;

		tempWrong[0][current] = increment + tempCorrect[current]; //this one starts at the second iteration (since it is always starts at 0)
		tempWrong[1][current] = i; //never true due to the offset condition
		tempWrong[2][current] -= offset;
		//just dont change the last wrong array, so its the same as the original

		current += increment;
	}

	CheckUniqueAnswers(tempCorrect, tempWrong);

	correct += "\\{";
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] += "\\{";
	}

	//get the answers ready for printing:
	for (int j = 0; j < size; j++)
	{
		correct += to_string(tempCorrect[j]) + ", ";

		for (size_t i = 0; i < wrong.size(); i++)
		{
			wrong[i] += to_string(tempWrong[i][j]) + ", ";
		}
	}

	correct.replace(correct.end() - 2, correct.end(), "\\}");
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i].replace(wrong[i].end() - 2, wrong[i].end(), "\\}");
	}
}

void Arrays::TypeThree()
{
	
}

void Arrays::TypeFour()
{
	
}

void Arrays::Tests()
{
	
}
