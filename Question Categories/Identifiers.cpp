

#include "identifiers.h"

const string Identifiers::LOWER = "abcdefghijklmnopqrstuvwxyz";

const string Identifiers::UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const string Identifiers::NUMBERS = "0123456789";

const string Identifiers::INVALID = "?!@#&.";


Identifiers::Identifiers() : Question(1) //only one wrong answer
{
	length = GenerateRand<int>(5, 10);
	valid = true;	//assume true and prove it's false
	id = "";
}

void Identifiers::TypeOne()
{
	GenerateRandId(false);
	
	PrintAndFinish();
}

void Identifiers::TypeTwo()
{
	GenerateRandId(false);
	
	PrintAndFinish();
}

void Identifiers::TypeThree()
{
	GenerateRandId(true);
	
	PrintAndFinish();
}

void Identifiers::TypeFour()
{
	GenerateRandId(true);
	
	PrintAndFinish();
}

void Identifiers::GenerateRandId(bool odds)
{
	int category;

	//Choosing a category to pull a char from
	//if odds, then pick from invalid and underscore characters too
	if (odds)
	{
		category = 10;
	}
	else
	{
		category = 8;
	}


	for (int i = 0; i < length; i++)
	{
		switch (GenerateRand<int>(0, category))
		{
			//Chance it is an uppercase letter
			case 0:
			case 1:
			case 2:
				id += UPPER[GenerateRand<int>(0, 26)];
				break;
			//Chance it is an lowercase letter
			case 3:
			case 4:
			case 5:
				id += LOWER[GenerateRand<int>(0, 26)];
				break;
			//Chance it is an numeral
			case 6:
			case 7:
				//if it's the first character it's invalid
				if (i == 0)
				{
					valid = false;
				}
				id += NUMBERS[GenerateRand<int>(0, 10)];
				break;
			//Chance it is an underscore
			case 8:
				id += '_';
				break;
			//Chance it is an invalid char
			case 9:
				id += INVALID[GenerateRand<int>(0, 6)];
				valid = false;
			break;
		}
	}
}

void Identifiers::PrintAndFinish()
{
	prompt += "Is the following a valid C++ identifier?\n";
	
	prompt += id + "\n";

	//If case to give the correct answer
	if (valid)
	{
		correct = "True";
		wrong[0] = "False";
	}
	else
	{
		correct = "False";
		wrong[0] = "True";
	}
}
