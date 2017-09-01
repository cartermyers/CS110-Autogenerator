#include "Conditionals.h"

void Conditionals::MainQ(int size, bool randomOrder)
{
	//initializes the data members based on size
	InitializeExpression(size);
	
	//prints the question prompt
	//and randomizes the data members if specified
	prompt += PrintPrompt(randomOrder);
	
	if (ComputeExpression())
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

void Conditionals::TypeOne()
{
	MainQ(2, false);
}

void Conditionals::TypeTwo()
{
	MainQ(3, false);
}

void Conditionals::TypeThree()
{
	MainQ(2, true);
}

void Conditionals::TypeFour()
{
	MainQ(3, true);
}

void Conditionals::InitializeExpression(int size)
{
	operands.size = size * 2; //each logical statement uses two operands here
	
	vector<int> temp(operands.size); //used to find unique ids for the variables
	
	//assign operands
	for (int i = 0; i < operands.size; i++)
	{
		//use all ints
		operands.dataTypes.push_back(Int);
		
		operands.vals.push_back(GenerateRand<float>(1, 11, 1)); //use random values between 1 and 10
		
		//only use variables for every second element
		if (i % 2 == 0)
		{
			temp.push_back(FindUnique(temp, temp.size(), IDENTIFIERS.size()));
		
			operands.ids.push_back(IDENTIFIERS[temp.back()]);
		}
		else
		{
			operands.ids.push_back(FloatToString(operands.vals[i]));
		}
		
		//and set the order as well
		operands.order.push_back(i);
	}
	
	//assign the operators:
	//always one less than the number of operands
	for (int i = 0; i < operands.size - 1; i++)
	{
		//every second operator is between operands
		//only use >, >=, <, <=,
		if (i % 2 == 0)
		{
			operators.push_back(GenerateRand<Symbols>(gt, lte + 1));	
		}
		//all other operators are between the results of the other operations
		//only use ==, !=, &&, ||
		else
		{
			operators.push_back(GenerateRand<Symbols>(eq, or + 1));
		}
	}
}

string Conditionals::PrintPrompt(bool randomOrder)
{
	string res = "What is the result of the following logical expression?\n";
	
	res += "<pre>";

	//declare all of the operands that are variables
	for (int i = 0; i < operands.size; i += 2)
	{
		res += 	DATA_TYPES[operands.dataTypes[i]] + " " + operands.ids[i] + " = " + FloatToString(operands.vals[i]) + ";\n";
	}
	
	//this gives the option to change the order of the declaration and the expression
	if (randomOrder)
	{
		random_shuffle(operands.order.begin(), operands.order.end());
		
		operands.ReorderStructure();
	}
	
	//now print the expression:
	//print the first little subexpression because it makes the loop go by smoother
	//For example if we have (a < 3) || (b >= 1), first print (a < 3) then print || (b >= 2) , etc. in the loop
	
	res += "(" + operands.ids[0] + " " + SYMBOLS[operators[0]] + " " + operands.ids[1] + ") ";
	
	for (int i = 2; i < operands.size; i += 2)
	{
		res += SYMBOLS[operators[i - 1]] + " (" + operands.ids[i] + " " + SYMBOLS[operators[i]] + " " + operands.ids[i + 1] + ") ";
	}
	
	res += "</pre>\n";
	
	return res;
}

bool Conditionals::ComputeExpression()
{
	return EvalExpression(operands.vals, operators);
}


bool Conditionals::EvalExpression(vector<float> vals, vector<Symbols> operators)
{
	assert(operators.size() == vals.size() - 1);

	vector<Symbols> tempOperators = operators;	//temporary vector, just a subset of the operators
												//this just makes calculations more clear

	//use a different loop to check for each operator precedence
	
	for (size_t i = 0; i < tempOperators.size();)
	{
		if (gt <= tempOperators[i] && tempOperators[i] <= lte)
		{
			vals[i] = Compare(tempOperators[i], vals[i], vals[i + 1]);
			
			//and delete the parts we used
			tempOperators.erase(tempOperators.begin() + i);
			vals.erase(vals.begin() + i + 1);
		}
		else
		{
			i++;
		}
	}
	
	vector<bool> tempRes;	//a temporary vector of the results of each parenthetical expression

	for (size_t i = 0; i < vals.size(); i++)
	{
		tempRes.push_back(bool(vals[i]));
	}

	assert(tempRes.size() - 1 == tempOperators.size());
	
	//check for != and == operators (next highest precedence)
	for (size_t i = 0; i < tempOperators.size(); ) //i is incremented in loop
	{
		if (tempOperators[i] == eq || tempOperators[i] == neq)
		{
			tempRes[i] = Question::Compare(tempOperators[i], tempRes[i], tempRes[i + 1]);
			
			//and delete the parts we used
			tempOperators.erase(tempOperators.begin() + i);
			tempRes.erase(tempRes.begin() + i + 1);
		}
		else
		{
			i++;	//we only need to increment i when we didn't delete anything
		}
	}
	
	assert(tempRes.size() - 1 == tempOperators.size());
	//do a similar pass over for &&
	for (size_t i = 0; i < tempOperators.size(); )
	{
		if (tempOperators[i] == and)
		{
			tempRes[i] = Question::Compare(tempOperators[i], tempRes[i], tempRes[i + 1]);
			
			//and delete the parts we used
			tempOperators.erase(tempOperators.begin() + i);
			tempRes.erase(tempRes.begin() + i + 1);
		}
		else
		{
			i++;
		}
	}
	
	assert(tempRes.size() - 1 == tempOperators.size());
	//and lastly, any values left in tempOperators should be ||
	//maybe we should just return true if we find a true value? since that's a property of ||
	//i'll leave it like this implementation for now because it's clearer i think
	while (tempOperators.size() > 0)
	{
		tempRes[0] = Question::Compare(tempOperators[0], tempRes[0], tempRes[1]);
			
		//and delete the parts we used
		tempOperators.erase(tempOperators.begin());
		tempRes.erase(tempRes.begin() + 1);
	}
	
	return tempRes[0];
}

void Conditionals::Tests()
{
	//test the EvalExpression function
	
	//first test each comparison operator individually
	//uses OperandSwitch as authority but that's okay because we've already tested that
	for (Symbols i = gt; i <= lte; i = Symbols(i + 1))
	{
		//1 i 2
		assert(EvalExpression({1, 2}, {i}) == Compare(i, 1, 2));
		//2 i 2
		assert(EvalExpression({2, 2}, {i}) == Compare(i, 2, 2));
		//3 i 2
		assert(EvalExpression({3, 2}, {i}) == Compare(i, 3, 2));
	}
	
	//test each logical oprator:
	for (Symbols i = eq; i <= or; i = Symbols(i + 1))
	{
		assert(EvalExpression({0, 0}, {i}) == Compare(i, 0, 0));
		assert(EvalExpression({0, 1}, {i}) == Compare(i, 0, 1));
		assert(EvalExpression({1, 0}, {i}) == Compare(i, 1, 0));
		assert(EvalExpression({1, 1}, {i}) == Compare(i, 1, 1));
	}
	
	//now test expressions of length 2 (meaning (var1 * lit) ** (var2 * lit))
	
	//(1 > 2) == (3 < 4)
	assert(!EvalExpression({1, 2, 3, 4}, {gt, eq, lt}));
	
	//(1 < 2) == (3 < 4)
	assert(EvalExpression({1, 2, 3, 4}, {lt, eq, lt}));
	
	//(1 < 2) == (3 > 4)
	assert(!EvalExpression({1, 2, 3, 4}, {lt, eq, gt}));
	
	//this checks neq
	//(1 > 2) != (3 < 4)
	assert(EvalExpression({1, 2, 3, 4}, {gt, neq, lt}));
	
	//2 <= 3 != 4 <= 5
	assert(!EvalExpression({2, 3, 4, 5}, {lte, neq, lt}));
	
	//check and:
	//(1 < 2) && (3 < 4)
	assert(EvalExpression({1, 2, 3, 4}, {lt, and, lt}));
	
	//6 > 7 && 8 <= 9
	assert(!EvalExpression({6, 7, 8, 9}, {gt, and, lte}));
	
	//5 <= 5 && 6 >= 7
	assert(!EvalExpression({5, 5, 6, 7}, {lte, and, gte}));
	
	//check or:
	//1 < 2 || 3 < 3
	assert(EvalExpression({1, 2, 3, 3}, {lt, or, lt}));	
	
	//1 < 1 || 1 > 1
	assert(!EvalExpression({1, 1, 1, 1}, {lt, or, gt}));
	
	//4 < 3 || 2 >= 1
	assert(EvalExpression({4, 3, 2, 1}, {lt, or, gte}));
	
	
	//now test expressions of length 3 (meaning (var1 * lit) ** (var2 * lit) ** (var3 * lit))
	
	
}