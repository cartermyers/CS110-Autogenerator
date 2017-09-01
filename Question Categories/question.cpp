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

//given some identifiers and operators
//this function will return an expression as half a statement
// in the form "A + B;\n"
string Question::PrintExpr(const vector<string>& operandIds,	//the identifers are already declared
						   const vector<Symbols>& operators)	//and so are the operators										
{
	//only support binary operators for now
	assert(operandIds.size() - 1 == operators.size());

	//initialize string with first operand
	string expr = operandIds[0];

	for (size_t i = 0; i < operators.size(); i++)
	{
		expr += " " + SYMBOLS[operators[i]] + " " + operandIds[i + 1];
	}

	expr += ";\n";

	return expr;
}


//searches the vector A up to lengthA and returns a value not in vector A
int Question::FindUnique(const vector<int>& A, int lengthA, int range)
{
	//make sure we can actually find a unique value
	assert(range > lengthA);

	int newVal = 0;
	bool unique = true;

	do
	{
		newVal = GenerateRand<int>(0, range);
		unique = true;

		for (int i = 0; i < lengthA; i++)
		{
			if (A[i] == newVal) //default 2 decimals of precision
			{
				unique = false;
				break;
			}
		}
	} while (!unique);

	return newVal;
}

float Question::Arithmetic(Symbols symb, float var1, DataTypes type1, float var2, DataTypes type2)
{
	//first, convert the values into their proper types
	//then, perform the operation
	//finally, convert the result to the most general datatype (in max)
	return Convert(max(type1, type2), Arithmetic(symb, Convert(type1, var1), Convert(type2, var2)));
}

float Question::EvalExpr(vector<float> operands, vector<DataTypes> types, vector<Symbols> operators, bool orderOfOps)
{
	assert(operands.size() - 1 == operators.size());
	assert(operands.size() == types.size());

	if (orderOfOps)
	{
		//first check for *, / or % operators:
		for (size_t i = 0; i < operators.size();) //i updated in loop
		{
			if (operators[i] <= mod)
			{
			  	//perform the operation
				operands[i] = Arithmetic(operators[i], operands[i], types[i], operands[i + 1], types[i + 1]);
				
				//if the second operand is float, it forces the first one to be float as well
				//in all other cases, the first operand keeps its original type (either float or int)
				if (types[i + 1] == Float)
				{
				  types[i] = Float;
				}
				
				operators.erase(operators.begin() + i);		//erase the operator because we no longer need it
				operands.erase(operands.begin() + i + 1);	//and erase the second operand because it was used as well (the first one was written over)
				types.erase(types.begin() + i + 1); 		//and erase the next type corresponding to the operand
			}
			else
			{
				i++; //move on to next element
			}
		}
	}

	//now do all the other operators:
	while (operators.size() > 0)
	{
		//if it is a postfix increment, just ignore it
		//NOTE: we will need to change the logic slightly here to allow a prefix increment
		//because this still only works on binary operators, it just ignores unary operators right now
		if (operators[0] != incr)
		{
			operands[0] = Arithmetic(operators[0], operands[0], types[0], operands[1], types[1]);
			
			//and propogate the datatype if we need to (see above for reasoning)
			if (types[1] == Float)
			{
				types[0] = Float;
			}
			
			operands.erase(operands.begin() + 1);
			types.erase(types.begin() + 1);
		}
		
		operators.erase(operators.begin());		//use same logic as above
	}

	return operands[0];
}

string Question::FloatToString(const float& val, bool isFixed, int precision)
{
	stringstream stream;

	if (isFixed)
	{
		stream << fixed;
	}

	stream << setprecision(precision) << val;
	return stream.str();
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
					random_shuffle(tempWrong[j].begin(), tempWrong[j].end());
				}
				else //we need to add a new random element
				{
					int temp = rand() % tempWrong[j].size();
					tempWrong[j][temp] = Arithmetic(add, tempWrong[j][temp], GenerateRand<int>(1, 5));
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
						random_shuffle(tempWrong[j].begin(), tempWrong[j].end());
					}
					else //we need to add a new random element
					{
						int temp = rand() % tempWrong[j].size();
						tempWrong[j][temp] = Arithmetic(add, tempWrong[j][temp], GenerateRand<int>(1, 5));
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

//------------------------------------------------------------variables stuff-----------------------------------------------------
Variables::Variables()
{
	size = 0;
}

Variables::Variables(int length) : size(length)
{
	for (int i = 0; i < length; i++)
	{
		order.push_back(i);
		//allocate other vectors with 0s or null:
		//this may be changed later
		//INVESTIGATE IF THIS CONSTRUCTOR IS ACTUALLY USEFUL IN ASSIGNING MEANINGFUL VALUES
		dataTypes.push_back(Int);
		ids.push_back("");
		vals.push_back(0);
	}
}

Variables::Variables(vector<DataTypes> types, vector<float> values, vector<string> identifiers) : dataTypes(types), vals(values), ids(identifiers)
{
	size = vals.size();
	for (int i = 0; i < size; i++)
	{
		order.push_back(i);
	}
}

//reorder all the vectors based on the order vector
void Variables::ReorderStructure()
{
	for (int i = 0; i < size; i++)
	{
		//first just append the values so we have the old order to reference
		ids.push_back(ids[order[i]]);
		vals.push_back(vals[order[i]]);
		dataTypes.push_back(dataTypes[order[i]]);
		
		//and once we reorder every single vector, we can set the order back to it's 
		//starting state
		order[i] = i;
	}
	//and erase the last parts:
	ids.erase(ids.begin(), ids.begin() + size);
	vals.erase(vals.begin(), vals.begin() + size);
	dataTypes.erase(dataTypes.begin(), dataTypes.begin() + size);
}

//------------------------------------------------------------parameters stuff-----------------------------------------------------

Parameters::Parameters() : Variables() {};

Parameters::Parameters(int length) : Variables(length)
{
	for (int i = 0; i < length; i++)
	{
		refs.push_back(false);
	}
}

Parameters::Parameters(vector<DataTypes> types, vector<float> values, vector<string> identifiers, vector<bool> ref)
						: Variables(types, values, identifiers)
{
	refs = ref;
}

//This would be a nice function to overload
//but maybe i need to change the parameters one in some way? virtual?
//compiler doesn't like it rn

void Parameters::ReorderStructure()
{
	for (int i = 0; i < size; i++)
	{
		refs.push_back(refs[order[i]]);
	}
	refs.erase(refs.begin(), refs.begin() + size);
	
	//and reorder the rest of the vectors
	this->Variables::ReorderStructure();
}

//Tests
void Question::Tests()
{
	//here are all of the sections for the tests (maybe I should make a function for each one of these?)

	//non-templated functions:

	//---------PrintExpr------------
	//"1 + 4;\n"
	assert(PrintExpr({ "1", "4" }, { add }) == "1 + 4;\n");
	//"hello * goodbye;\n"
	assert(PrintExpr({ "hello", "goodbye" }, { mul }) == "hello * goodbye;\n");
	//"this / that;\n"
	assert(PrintExpr({ "this", "that" }, { divide }) == "this / that;\n");
	//"1 / 0 - 1_thing;\n" - not a valid expression but its supported (user should use best judgement)
	assert(PrintExpr({ "1", "0", "1_thing" }, { divide, sub }) == "1 / 0 - 1_thing;\n");

	//---------FindUnique---------------
	assert(FindUnique({ 0 }, 1, 2) == 1);
	assert(FindUnique({}, 0, 1) == 0);
	assert(FindUnique({ 0, 1, 3, 4 }, 4, 5) == 2);
	assert(FindUnique({ 0, 1, 2 }, 3, 4) == 3);

	//-------------------------------------Arithmetic-----------------------------------------
	//for operands with different datatypes

	//division with proper datatypes:
	//1 / 3 == 0
	assert(Compare(eq, Arithmetic(divide, 1.0, Int, 3.0, Int), 1 / 3));
	//1 / 3.0 == 0.333
	assert(Compare(eq, Arithmetic(divide, 1, Int, 3, Float), 1 / 3.0));
	//1.0 / 3 == 0.333
	assert(Compare(eq, Arithmetic(divide, 1, Float, 3, Int), 1.0 / 3));
	//1.0 / 3.0 == 0.333
	assert(Compare(eq, Arithmetic(divide, 1, Float, 3, Float), 1.0 / 3.0));

	//now assuming the datatypes are wrong:
	//Int(1.5) / 3 == 0
	assert(Compare(eq, Arithmetic(divide, 1.5, Int, 3, Int), int(1.5) / 3));
	//Int(1.5) / 3.0 == 0.333
	assert(Compare(eq, Arithmetic(divide, 1.5, Int, 3, Float), int(1.5) / 3.0));
	//1.5 / Int(3.5) == 0.5
	assert(Compare(eq, Arithmetic(divide, 1.5, Float, 3.5, Int), 1.5 / int(3.5)));

	//addition with right datatypes:
	// 2 + 4 = 6
	assert(Compare(eq, Arithmetic(add, 2, Int, 4, Int), 2 + 4));
	// 2 + 4.5 = 6.5
	assert(Compare(eq, Arithmetic(add, 2, Int, 4.5, Float), 2 + 4.5));
	// 2.6 + 4 = 6.6
	assert(Compare(eq, Arithmetic(add, 2.6f, Float, 4, Int), 2.6f + 4));
	// 2.5 + 4.3 = 6.8
	assert(Compare(eq, Arithmetic(add, 2.5f, Float, 4.3f, Float), 2.5f + 4.3f));

	//now with wrong datatypes:
	// int(4.7) + int(1.1) == 5
	assert(Compare(eq, Arithmetic(add, 4.7f, Int, 1.1f, Int), int(4.7) + int(1.1)));
	// 4.7 + int(1.1) == 5.7
	assert(Compare(eq, Arithmetic(add, 4.7f, Float, 1.1f, Int), 4.7f + int(1.1)));
	// int(4.7) + 1.1 == 5.1
	assert(Compare(eq, Arithmetic(add, 4.7f, Int, 1.1f, Float), int(4.7) + 1.1f));

	//multiplication with right datatypes:
	// 5 * 3 == 15
	assert(Compare(eq, Arithmetic(mul, 5, Int, 3, Int), 5 * 3));
	// 5.1 * 3 = 15.3
	assert(Compare(eq, Arithmetic(mul, 5.1f, Float, 3, Int), 5.1f * 3));
	// 5 * 3.1 == 15.5
	assert(Compare(eq, Arithmetic(mul, 5, Int, 3.1f, Float), 5 * 3.1f));
	// 5.5 * 3.3 = 15.3
	assert(Compare(eq, Arithmetic(mul, 5.5f, Float, 3.3f, Float), 5.5f * 3.3f));

	//multiplication with wrong datatypes:
	// int(5.5) * int(3.3) == 15
	assert(Compare(eq, Arithmetic(mul, 5.5f, Int, 3.3f, Int), int(5.5) * int(3.3)));
	// 5.5 * int(3.3) == 16.5
	assert(Compare(eq, Arithmetic(mul, 5.5f, Float, 3.3f, Int), 5.5f * int(3.3)));
	// int(5.5) * 3.3 == 16.5
	assert(Compare(eq, Arithmetic(mul, 5.5f, Int, 3.3f, Float), int(5.5) * 3.3f));

	//subtraction with right datatypes:
	// 7 - 2 = 5
	assert(Compare(eq, Arithmetic(sub, 7, Int, 2, Int), 7 - 2));
	// 7.5 - 2 = 5.5
	assert(Compare(eq, Arithmetic(sub, 7.5f, Float, 2, Int), 7.5f - 2));
	// 7 - 2.5 = 4.5
	assert(Compare(eq, Arithmetic(sub, 7, Int, 2.5f, Float), 7 - 2.5f));
	// 7.4 - 2.6 = 4.8
	assert(Compare(eq, Arithmetic(sub, 7.4f, Float, 2.6f, Float), 7.4f - 2.6f));

	//subtraction with wrong datatypes:
	// int(7.4) - int(2.6) = 5
	assert(Compare(eq, Arithmetic(sub, 7.4f, Int, 2.6f, Int), int(7.4) - int(2.6)));
	// 7.4 - int(2.6) = 5.4
	assert(Compare(eq, Arithmetic(sub, 7.4f, Float, 2.6f, Int), 7.4f - int(2.6)));
	// int(7.4) - 2.6 = ?
	assert(Compare(eq, Arithmetic(sub, 7.4f, Int, 2.6f, Float), int(7.4) - 2.6f));

	//mod with right datatypes:
	// NOTE: i only test int here because float operands shouldn't use the built in operator
	// even though this function uses fmod and can handle floats

	// 9 % 4 = 1
	assert(Compare(eq, Arithmetic(mod, 9, Int, 4, Int), 9 % 4));

	//----EvalExpr----
	//for operands with different types

	//4.0 / 6 - 1 == -0.3333...
	assert(Compare(eq, EvalExpr({ 4, 6, 1 }, { Float, Int, Int }, { divide, sub }), 4.0 / 6 - 1));
	//4 / 6 - 1 == -1
	assert(Compare(eq, EvalExpr({ 4, 6, 1 }, { Int, Int, Int }, { divide, sub }), 4 / 6 - 1));
	//7.0 * 6 - 6.0
	assert(Compare(eq, EvalExpr({ 7, 6, 6 }, { Float, Int, Float }, { mul, sub }), 7.0 * 6 - 6.0));
	//1 + 3 / 2.0 == 2.5
	assert(Compare(eq, EvalExpr({ 1, 3, 2 }, { Int, Int, Float }, { add, divide }), 1 + 3 / 2.0));
	//1 + 3.0 / 2 == 2.5
	assert(Compare(eq, EvalExpr({ 1, 3, 2 }, { Int, Float, Int }, { add, divide }), 1 + 3.0 / 2));
	//1.0 + 3 / 2 == 2
	assert(Compare(eq, EvalExpr({ 1, 3, 2 }, { Float, Int, Int }, { add, divide }), 1.0 + 3 / 2));

	//template stuff:

	//---------Arithmetic------------
	//int:
	//2 * 4 == 8
	assert(Arithmetic<int>(mul, 2, 4) == 8);

	//7 / 3 == 2
	assert(Arithmetic<int>(divide, 7, 3) == 2);
	//1 / 0 == 0
	assert(Arithmetic<int>(divide, 1, 0) == 0);
	//10 / 2 == 5
	assert(Arithmetic<int>(divide, 10, 2) == 5);

	//5 % 1 == 0
	assert(Arithmetic<int>(mod, 5, 1) == 0);
	//4 % 0 == 4
	assert(Arithmetic<int>(mod, 4, 0) == 4);
	//7 % 4 == 3
	assert(Arithmetic<int>(mod, 7, 4) == 3);

	//5 + 3 == 8
	assert(Arithmetic<int>(add, 5, 3) == 8);

	//3 - 6 == -3
	assert(Arithmetic<int>(sub, 3, 6) == -3);
	//6 - 3 == 3
	assert(Arithmetic<int>(sub, 6, 3) == 3);

	//5++ == 6 (or ++5 == 6 more realistically)
	assert(Arithmetic<int>(incr, 5, -5) == 6);

	// 3 > 2
	assert(Compare(gt, 3, 2));
	// ! 5 > 5 
	assert(!Compare(gt, 5, 5));
	// ! 4 > 6
	assert(!Compare(gt, 4, 6));

	//3 >= 2
	assert(Compare(gte, 3, 2));
	//5 >= 5
	assert(Compare(gte, 5, 5));
	// ! 4 >= 6
	assert(!Compare(gte, 4, 6));

	// 1 < 6
	assert(Compare(lt, 1, 6));
	// ! 7 < 7 == 0
	assert(!Compare(lt, 7, 7));
	// ! 10 < 9 == 0
	assert(!Compare(lt, 10, 9));

	// 5 <= 6
	assert(Compare(lte, 5, 6));
	// 6 <= 6
	assert(Compare(lte, 6, 6));
	// ! 3 <= 2
	assert(!Compare(lte, 3, 2));

	//TEST FLOAT STUFF?
	//AND BOOL STUFF?
	//quick note: don't call it like Arithmetic<bool> because it converts the parameters to bool

	//------------EvalExpr-----------
	// 1 + 2 == 3
	assert(EvalExpr<int>({ 1, 2 }, { add }) == 3);
	// 5 - 6 == -1
	assert(EvalExpr<int>({ 5, 6 }, { sub }) == -1);
	// 3 * 4 == 12
	assert(EvalExpr<int>({ 3, 4 }, { mul }) == 12);
	// 6 / 5 == 1
	assert(EvalExpr<int>({ 6, 5 }, { divide }) == 1);
	// 7 % 3 == 1
	assert(EvalExpr<int>({ 7, 3 }, { mod }) == 1);

	//longer stuff now:
	//4 * 2.0 / 5 == 1.6
	assert(Compare(eq, EvalExpr<float>({ 4, 2, 5 }, { mul, divide }), 4 * 2.0 / 5));

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