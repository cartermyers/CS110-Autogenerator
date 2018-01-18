

#include "QIdentifiers.h"

const string QIdentifiers::LOWER = "abcdefghijklmnopqrstuvwxyz";

const string QIdentifiers::UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const string QIdentifiers::NUMBERS = "0123456789";

const string QIdentifiers::INVALID = "?!@#&.";


QIdentifiers::QIdentifiers() : Question(1) //only one wrong answer
{
	length = GenerateRand<int>(5, 9);
	valid = true;	//assume true and prove it's false
	id = "";
}

void QIdentifiers::TypeOne()
{
	GenerateRandId(false);
	
	PrintAndFinish();
}

void QIdentifiers::TypeTwo()
{
	GenerateRandId(false);
	
	PrintAndFinish();
}

void QIdentifiers::TypeThree()
{
	GenerateRandId(true);
	
	PrintAndFinish();
}

void QIdentifiers::TypeFour()
{
	GenerateRandId(true);
	
	PrintAndFinish();
}

void QIdentifiers::GenerateRandId(bool odds)
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
		switch (GenerateRand<int>(0, category - 1))
		{
			//Chance it is an uppercase letter
			case 0:
			case 1:
			case 2:
				id += UPPER[GenerateRand<int>(0, UPPER.size() - 1)];
				break;
			//Chance it is an lowercase letter
			case 3:
			case 4:
			case 5:
				id += LOWER[GenerateRand<int>(0, LOWER.size() - 1)];
				break;
			//Chance it is an numeral
			case 6:
			case 7:
				//if it's the first character it's invalid
				if (i == 0)
				{
					valid = false;
				}
				id += NUMBERS[GenerateRand<int>(0, NUMBERS.size() - 1)];
				break;
			//Chance it is an underscore
			case 8:
				id += '_';
				break;
			//Chance it is an invalid char
			case 9:
				id += INVALID[GenerateRand<int>(0, INVALID.size() - 1)];
				valid = false;
			break;
		}
	}
}

void QIdentifiers::PrintAndFinish()
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
