#include "QConditionals.h"

//TODO: EXPRESSIONS
// USE NEW CLASS
// USE NEW VARIABLESVEC CLASS AS WELL


QConditionals::QConditionals() : Question(1)
{
	//don't need to do anything real here because it's handled in InitializeExpr
	expr = NULL;
}


QConditionals::~QConditionals()
{
	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}
}


void QConditionals::MainQ(int size, bool randomOrder)
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

void QConditionals::TypeOne()
{
	MainQ(2, false);
}

void QConditionals::TypeTwo()
{
	MainQ(3, false);
}

void QConditionals::TypeThree()
{
	MainQ(2, true);
}

void QConditionals::TypeFour()
{
	MainQ(3, true);
}

void QConditionals::InitializeExpression(int size)
{
	/*
		GENERAL OVERVIEW

		Basically, this function generates statements of the form
		(sub-expression) || (sub-expression) == (sub-expression)

		where size is the number of sub_expressions

		and a sub-expression is of the form
		(a > 9)

		and a is a previously declared variable.

		So we must generate all variables and the expression (in the form of a string)
		which is then used to initialized the private member "expr".	
	*/
	
	Variable tempVar;

	VariablesVec tempOperands;
	vector<int> tempIndex(size); //used to find unique ids for the variables

	vector<string> tempExpr;	//create a temporary expression in the form of its tokens.
								//this allows us to (somewhat manually) create our own custom expression and then initialize it to an Expressions type

	//now create the expression by one HALF sub-expression at a time
	for (int i = 0; i < size * 2; i++)
	{
		//use all ints
		tempVar.type = Int;
		tempVar.val = GenerateRand<int>(1, 10); //use random values between 1 and 10
		
		//only use variables for the first operand in each subexpression
		if (i % 2 == 0)
		{
			tempIndex.push_back(FindUnique(tempIndex, tempIndex.size(), IDENTIFIERS.size() - 1));
			tempVar.id = IDENTIFIERS[tempIndex.back()];

			//expression:
			tempExpr.push_back("(");
			tempExpr.push_back(tempVar.id);
			tempExpr.push_back(SYMBOLS[GenerateRand<Symbols>(gt, lte)]);
		}
		else
		{
			tempVar.id = FloatToString(tempVar.val);

			//expression:
			tempExpr.push_back(tempVar.id);
			tempExpr.push_back(")");
			tempExpr.push_back(SYMBOLS[GenerateRand<Symbols>(or , neq)]);
		}
		
		//and add to the variables
		tempOperands.AddVariable(tempVar, false);
	}
	
	//remove the last operator in the expression (which is always one of ||, &&, ==, !=
	tempExpr.pop_back();

	//finally, initialize the expression:
	assert(expr == NULL);
	expr = new Expressions(tempExpr, &tempOperands, false);
}

string QConditionals::PrintPrompt(bool randomOrder)
{
	string res = "What is the result of the following logical expression?\n";
	
	res += "<pre>";

	//this gives the option to change the order of the declaration and the expression
	if (randomOrder)
	{
		expr->RandomizeVariablesDefinition();
	}

	//declare all of the operands that are variables
	res += expr->GetVariables().Print();
	
	//now print the expression:
	res += expr->Print();
	
	res += "</pre>\n";
	
	return res;
}

bool QConditionals::ComputeExpression()
{
	return (bool)expr->Eval();
}

void QConditionals::Tests()
{
	
	//test the ComputeExpression function
	
	if (expr != NULL)
	{
		delete expr;
		expr = NULL;
	}

	//here is a VariablesVec of literals that we will use for testing
	VariablesVec tester({ Variable("0", Int, 0), Variable("1", Int, 1), Variable("2", Int, 2), Variable("3", Int, 3), Variable("4", Int, 4), Variable("5", Int, 5), Variable("6", Int, 6), Variable("7", Int, 7) });


	//first test each comparison operator individually
	//uses Operation as authority but that's okay because we've already tested that
	for (Symbols i = gt; i <= lte; i = Symbols(i + 1))
	{
		//1 i 2
		expr = new Expressions({ "1", SYMBOLS[i], "2" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 1, 2));
		delete expr;
		expr = NULL;

		//2 i 2
		expr = new Expressions({ "2", SYMBOLS[i], "2" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 2, 2));
		delete expr;
		expr = NULL;

		//3 i 2
		expr = new Expressions({ "3", SYMBOLS[i], "2" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 3, 2));
		delete expr;
		expr = NULL;
	}
	
	//test each logical oprator:
	for (Symbols i = or; i <= neq; i = Symbols(i + 1))
	{
		expr = new Expressions({ "0", SYMBOLS[i], "0" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 0, 0));
		delete expr;
		expr = NULL;

		expr = new Expressions({ "0", SYMBOLS[i], "1" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 0, 1));
		delete expr;
		expr = NULL;

		expr = new Expressions({ "1", SYMBOLS[i], "0" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 1, 0));
		delete expr;
		expr = NULL;

		expr = new Expressions({ "1", SYMBOLS[i], "1" }, &tester);
		assert(ComputeExpression() == Operation<bool>(i, 1, 1));
		delete expr;
		expr = NULL;
	}
	
	//now test expressions of length 2 (meaning (var1 * lit) ** (var2 * lit))

	//(1 > 2) == (3 < 4)	(equates to false)
	expr = new Expressions({ "(", "1", ">", "2", ")", "==", "(", "3", "<", "4", ")" }, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;

	//(1 < 2) == (3 < 4)	(true)
	expr = new Expressions({ "(", "1", "<", "2", ")", "==", "(", "3", "<", "4", ")" }, &tester);
	assert(ComputeExpression());
	delete expr;
	expr = NULL;
	
	//(1 < 2) == (3 > 4)	(false)
	expr = new Expressions({ "(", "1", "<", "2", ")", "==", "(", "3", ">", "4", ")" }, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;
	
	//this checks neq
	//(1 > 2) != (3 < 4)	(true)
	expr = new Expressions({ "(", "1", ">", "2", ")", "!=", "(", "3", "<", "4", ")" }, &tester);
	assert(ComputeExpression());
	delete expr;
	expr = NULL;
	
	//2 <= 3 != 4 <= 5		(false)
	expr = new Expressions({ "2", "<=", "3", "!=", "4", "<=", "5"}, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;
	
	//check and:
	//(1 < 2) && (3 < 4)	(true)
	expr = new Expressions({ "(", "1", "<", "2", ")", "&&", "(", "3", "<", "4", ")" }, &tester);
	assert(ComputeExpression());
	delete expr;
	expr = NULL;
	
	//6 > 7 && 8 <= 9	(false)
	expr = new Expressions({ "(", "6", ">", "7", ")", "&&", "(", "2", "<=", "5", ")" }, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;
	
	//5 <= 5 && 6 >= 7	(false)
	expr = new Expressions({ "5", "<=", "5", "&&", "6", ">=", "7" }, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;
	
	//check or:
	//1 < 2 || 3 < 3	(true)
	expr = new Expressions({ "1", "<", "2", "||", "3", "<", "3" }, &tester);
	assert(ComputeExpression());
	delete expr;
	expr = NULL;
	
	//(1 < 1) || (1 > 1)	(false)
	expr = new Expressions({ "(", "1", "<", "1", ")", "||", "(", "1", ">", "1", ")" }, &tester);
	assert(!ComputeExpression());
	delete expr;
	expr = NULL;
	
	//(4 < 3) || (2 >= 1)	(true)
	expr = new Expressions({ "(", "4", "<", "3", ")", "||", "(", "2", ">=", "1", ")" }, &tester);
	assert(ComputeExpression());
	delete expr;
	expr = NULL;
	
	
	//now test expressions of length 3 (meaning (var1 * lit) ** (var2 * lit) ** (var3 * lit))
	
}