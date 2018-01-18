//--------------------------------------------
//
// Implementation of the Question Superclass
//
//--------------------------------------------

#include "question.h"

Question::Question() 
{
	difficulty = 1;
	prompt = "";
	correct = "";
	for (int i = 0; i < 4; i++)
	{
		wrong.push_back("");
	}
}

Question::Question(int wrongSize)
{
	difficulty = 1;
	prompt = "";
	correct = "";
	for (int i = 0; i < wrongSize; i++)
	{
		wrong.push_back("");
	}
}

void Question::Print(ofstream& out)
{
	//first prompt:
	out << prompt;

	out << "\t{\n";
	//correct Answer
	out << "\t=" + correct << endl;

	// four wrong answers:
	for (size_t i = 0; i < wrong.size(); i++)
	{
		out << "\t~" + wrong[i] << endl;
	}

	out << "\t}\n\n";
}

void Question::Generate()
{
	switch (difficulty)
	{
	case 1:
		TypeOne();
		break;
	case 2:
		TypeTwo();
		break;
	case 3:
		TypeThree();
		break;
	case 4:
		TypeFour();
		break;
	default:
		prompt += "Please select proper difficulty.\n";
	}
}

void Question::SetDifficulty(int difficult)
{
	difficulty = difficult;
}

void Question::FinalAnswerCheck()
{
	for (size_t i = 0; i < wrong.size(); i++)
	{
		if (wrong[i].compare(correct) == 0)
		{
			SameAnswers a(correct, wrong);
			throw a;
		}
	
		//check the rest of the array
		for (size_t j = i + 1; j < wrong.size(); j++)
		{
			if (wrong[i].compare(wrong[j]) == 0)
			{
				SameAnswers a(correct, wrong);
				throw a;
			}
		}
	}
}

int Question::Factorial(int n)
{
	int res = 1;
	while (n > 0)
	{
		res *= n;
		n--;
	}
	return res;
}

int Question::NumOfPermutations(vector<int> original)
{
	set<int> unique(original.begin(), original.end()); //unique entries in the original
	vector<int> counts;

	//count the number of occurances in the original for each unique element
	for (set<int>::iterator i = unique.begin(); i != unique.end(); i++)
	{
		counts.push_back(count(original.begin(), original.end(), *i));
	}

	//now compute the product for the denominator (see equation above)
	int denominator = 1;
	for (size_t i = 0; i < counts.size(); i++)
	{
		denominator *= Factorial(counts[i]);
	}

	return Factorial(original.size()) / denominator;
}

//if we're using arrays with repeating elements we must have a condition as 
// Total number of answers <= factorial(number of elements) / factorial(number of repeated entry #1) * ... for every repeated number
// EX:
//		5 answers (1 correct, 4 wrong). Array is {1, 1, 1, 2}
//		factorial(4) / factorial(3) == 4
//		Therefore, we can only rearrange this array in 4 distinct ways, so it doesn't work.
// Ex:
//		5 answers. Array is {1, 1, 2, 2}
//		factorial(4) / (factorial(2) * factorial(2)) == 6
//		this works because there are 6 distinct ways to rearrange the array 
void Question::CheckUniqueAnswers(const vector<int>& tempCorrect, vector<vector<int>>& tempWrong)
{
	size_t n = tempWrong.size();
	bool unique = true; //a flag to see if we need to recheck answers

	//the number of ways we can distinctly arrange the original vector:
	unsigned int permutations = NumOfPermutations(tempCorrect); //this is computed to see if we can just rearrange the vector, or if we have to add elements

	//for every wrong vector
	for (size_t j = 0; j < n; j++)
	{
		do
		{
			unique = true;

			//make sure it is not the same as the correct one
			while (IsSame(tempWrong[j], tempCorrect))
			{
				//if this condition holds, we can just randomly rearrange the elements
				if (permutations >= (n + 1))
				{
					tempWrong[j] = tempCorrect;
					random_shuffle(tempWrong[j].begin(), tempWrong[j].end());
				}
				else //we need to add a new random element
				{
					int temp = rand() % tempWrong[j].size();
					tempWrong[j][temp] = Operation<int>(add, tempWrong[j][temp], GenerateRand<int>(1, 4));
				}
			}

			//and compare it to each other wrong vector
			for (size_t i = j + 1; i < (n + j); i++)
			{
				if (IsSame(tempWrong[j], tempWrong[i % n]))
				{
					//if this condition holds, we can just randomly rearrange the elements
					if (permutations >= (n + 1))
					{
						tempWrong[j] = tempCorrect;
						random_shuffle(tempWrong[j].begin(), tempWrong[j].end());
					}
					else //we need to add a new random element
					{
						int temp = rand() % tempWrong[j].size();
						tempWrong[j][temp] = Operation<int>(add, tempWrong[j][temp], GenerateRand<int>(1, 4));
					}
					unique = false;	//recheck every other vector if we changed the current vector
					break;
				}
			}
		} while (!unique);
	}
}

bool Question::IsSame(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  
  for (size_t i = 0; i < a.size(); i++)
  {
	if (a[i] != b[i])
	{
	  return false;
	}
  }
  
  return true;
}

//Tests
void Question::Tests()
{
	//here are all of the sections for the tests (maybe I should make a function for each one of these?)

	//non-templated functions:

	//---------FindUnique---------------
	assert(FindUnique({ 0 }, 1, 1) == 1);
	assert(FindUnique({}, 0, 0) == 0);
	assert(FindUnique({ 0, 1, 3, 4 }, 4, 4) == 2);
	assert(FindUnique({ 0, 1, 2 }, 3, 3) == 3);

	//-------------------------------------Operation-----------------------------------------
	//for operands with different datatypes

	//division with proper datatypes:
	//1 / 3 == 0
	assert(Operation<int>(eq, Operation(divide, 1.0, Int, 3.0, Int), 1 / 3));
	//1 / 3.0 == 0.333
	assert(Operation<float>(eq, Operation(divide, 1, Int, 3, Float), 1 / 3.0));
	//1.0 / 3 == 0.333
	assert(Operation<float>(eq, Operation(divide, 1, Float, 3, Int), 1.0 / 3));
	//1.0 / 3.0 == 0.333
	assert(Operation<float>(eq, Operation(divide, 1, Float, 3, Float), 1.0 / 3.0));

	//now assuming the datatypes are wrong:
	//Int(1.5) / 3 == 0
	assert(Operation<int>(eq, Operation(divide, 1.5, Int, 3, Int), int(1.5) / 3));
	//Int(1.5) / 3.0 == 0.333
	assert(Operation<float>(eq, Operation(divide, 1.5, Int, 3, Float), int(1.5) / 3.0));
	//1.5 / Int(3.5) == 0.5
	assert(Operation<float>(eq, Operation(divide, 1.5, Float, 3.5, Int), 1.5 / int(3.5)));

	//addition with right datatypes:
	// 2 + 4 = 6
	assert(Operation<int>(eq, Operation(add, 2, Int, 4, Int), 2 + 4));
	// 2 + 4.5 = 6.5
	assert(Operation<float>(eq, Operation(add, 2, Int, 4.5, Float), 2 + 4.5));
	// 2.6 + 4 = 6.6
	assert(Operation<float>(eq, Operation(add, 2.6f, Float, 4, Int), 2.6f + 4));
	// 2.5 + 4.3 = 6.8
	assert(Operation<float>(eq, Operation(add, 2.5f, Float, 4.3f, Float), 2.5f + 4.3f));

	//now with wrong datatypes:
	// int(4.7) + int(1.1) == 5
	assert(Operation<int>(eq, Operation(add, 4.7f, Int, 1.1f, Int), int(4.7) + int(1.1)));
	// 4.7 + int(1.1) == 5.7
	assert(Operation<float>(eq, Operation(add, 4.7f, Float, 1.1f, Int), 4.7f + int(1.1)));
	// int(4.7) + 1.1 == 5.1
	assert(Operation<float>(eq, Operation(add, 4.7f, Int, 1.1f, Float), int(4.7) + 1.1f));

	//multiplication with right datatypes:
	// 5 * 3 == 15
	assert(Operation<int>(eq, Operation(mul, 5, Int, 3, Int), 5 * 3));
	// 5.1 * 3 = 15.3
	assert(Operation<float>(eq, Operation(mul, 5.1f, Float, 3, Int), 5.1f * 3));
	// 5 * 3.1 == 15.5
	assert(Operation<float>(eq, Operation(mul, 5, Int, 3.1f, Float), 5 * 3.1f));
	// 5.5 * 3.3 = 15.3
	assert(Operation<float>(eq, Operation(mul, 5.5f, Float, 3.3f, Float), 5.5f * 3.3f));

	//multiplication with wrong datatypes:
	// int(5.5) * int(3.3) == 15
	assert(Operation<int>(eq, Operation(mul, 5.5f, Int, 3.3f, Int), int(5.5) * int(3.3)));
	// 5.5 * int(3.3) == 16.5
	assert(Operation<float>(eq, Operation(mul, 5.5f, Float, 3.3f, Int), 5.5f * int(3.3)));
	// int(5.5) * 3.3 == 16.5
	assert(Operation<float>(eq, Operation(mul, 5.5f, Int, 3.3f, Float), int(5.5) * 3.3f));

	//subtraction with right datatypes:
	// 7 - 2 = 5
	assert(Operation<int>(eq, Operation(sub, 7, Int, 2, Int), 7 - 2));
	// 7.5 - 2 = 5.5
	assert(Operation<float>(eq, Operation(sub, 7.5f, Float, 2, Int), 7.5f - 2));
	// 7 - 2.5 = 4.5
	assert(Operation<float>(eq, Operation(sub, 7, Int, 2.5f, Float), 7 - 2.5f));
	// 7.4 - 2.6 = 4.8
	assert(Operation<float>(eq, Operation(sub, 7.4f, Float, 2.6f, Float), 7.4f - 2.6f));

	//subtraction with wrong datatypes:
	// int(7.4) - int(2.6) = 5
	assert(Operation<int>(eq, Operation(sub, 7.4f, Int, 2.6f, Int), int(7.4) - int(2.6)));
	// 7.4 - int(2.6) = 5.4
	assert(Operation<float>(eq, Operation(sub, 7.4f, Float, 2.6f, Int), 7.4f - int(2.6)));
	// int(7.4) - 2.6 = ?
	assert(Operation<float>(eq, Operation(sub, 7.4f, Int, 2.6f, Float), int(7.4) - 2.6f));

	//mod with right datatypes:
	// NOTE: i only test int here because float operands shouldn't use the built in operator
	// even though this function uses fmod and can handle floats

	// 9 % 4 = 1
	assert(Operation<int>(eq, Operation(mod, 9, Int, 4, Int), 9 % 4));

	//template stuff:

	//---------Operation------------
	//int:
	//2 * 4 == 8
	assert(Operation<int>(mul, 2, 4) == 8);

	//7 / 3 == 2
	assert(Operation<int>(divide, 7, 3) == 2);
	//1 / 0 == 0
	assert(Operation<int>(divide, 1, 0) == 0);
	//10 / 2 == 5
	assert(Operation<int>(divide, 10, 2) == 5);

	//5 % 1 == 0
	assert(Operation<int>(mod, 5, 1) == 0);
	//4 % 0 == 4
	assert(Operation<int>(mod, 4, 0) == 4);
	//7 % 4 == 3
	assert(Operation<int>(mod, 7, 4) == 3);

	//5 + 3 == 8
	assert(Operation<int>(add, 5, 3) == 8);

	//3 - 6 == -3
	assert(Operation<int>(sub, 3, 6) == -3);
	//6 - 3 == 3
	assert(Operation<int>(sub, 6, 3) == 3);

	//5++ == 6 (or ++5 == 6 more realistically)
	assert(Operation<int>(incr, 5, -5) == 6);

	// 3 > 2
	assert(Operation<bool>(gt, 3, 2));
	// ! 5 > 5 
	assert(!Operation<bool>(gt, 5, 5));
	// ! 4 > 6
	assert(!Operation<bool>(gt, 4, 6));

	//3 >= 2
	assert(Operation<bool>(gte, 3, 2));
	//5 >= 5
	assert(Operation<bool>(gte, 5, 5));
	// ! 4 >= 6
	assert(!Operation<bool>(gte, 4, 6));

	// 1 < 6
	assert(Operation<bool>(lt, 1, 6));
	// ! 7 < 7 == 0
	assert(!Operation<bool>(lt, 7, 7));
	// ! 10 < 9 == 0
	assert(!Operation<bool>(lt, 10, 9));

	// 5 <= 6
	assert(Operation<bool>(lte, 5, 6));
	// 6 <= 6
	assert(Operation<bool>(lte, 6, 6));
	// ! 3 <= 2
	assert(!Operation<bool>(lte, 3, 2));

	//TEST FLOAT STUFF?

	//test Convert:
	//int(1.5)
	assert(Convert(Int, 1.5) == 1.0);
	//float(1.5)
	assert(Convert(Float, 1.5) == 1.5);
	//float(1)
	assert(Convert(Float, 1) == 1.0);
	//int(1)
	assert(Convert(Int, 1) == 1.0);

	//test IsSame? it's already in use above; sort of an implicit test
	//test FloatToString? maybe

	//test Variables stuff?
}