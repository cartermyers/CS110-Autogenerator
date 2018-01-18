//*******************************************************************************************
//							QExpressions SUBCLASS DEFINITIONS	
//
//*******************************************************************************************

//TODO EXPRESSIONS:
// REQRITE EVERYTHING TO NEW CLASS

#include "question.h"
#include "QExpressions.h"

void QExpressions::Tests()
{
	//---------PrintExpr------------
	//"1 + 4"
	assert(Expressions({ "1", "+", "4" }).Print() == "1 + 4");
	//"hello * goodbye;\n"
	assert(Expressions({ "hello", "*", "goodbye" }).Print() == "hello * goodbye");

	//now with parentheses:
	assert(Expressions({ "2", "*", "(", "what", "+", "3", ")" }).Print() == "2 * (what + 3)");

	//now with postfix incrementer (assumed)
	assert(Expressions({ "this", "++", "+",  "that" }).Print() == "this++ + that");

	//----EvalExpr----
	//for operands with different types
	
	//4.0 / 6 - 1 == -0.3333...
	VariablesVec temp1({ Variable("4", Float, 4), Variable("6", Int, 6), Variable("1", Int, 1) });
	assert(Operation<bool>(eq, Expressions({ "4", "/", "6", "-", "1" }, &temp1).Eval(), 4.0 / 6 - 1));

	//4 / 6 - 1 == -1
	VariablesVec temp2({ Variable("4", Int, 4), Variable("6", Int, 6), Variable("1", Int, 1) });
	assert(Operation<bool>(eq, Expressions({ "4", "/", "6", "-", "1" }, &temp2).Eval(), 4 / 6 - 1));

	//7.0 * 6 - 6.0
	VariablesVec temp3({ Variable("7", Float, 7), Variable("6", Int, 6), Variable("6.0", Float, 6) });
	assert(Operation<bool>(eq, Expressions({ "7", "*", "6", "-", "6.0" }, &temp3).Eval(), 7.0 * 6 - 6.0));

	//1 + 3 / 2.0 == 2.5
	VariablesVec temp4({ Variable("1", Int, 1), Variable("3", Int, 3), Variable("2", Float, 2) });
	assert(Operation<bool>(eq, Expressions({ "1", "+", "3", "/", "2" }, &temp4).Eval(), 1 + 3 / 2.0));

	//1 + 3.0 / 2 == 2.5
	VariablesVec temp5({ Variable("1", Int, 1), Variable("3", Float, 3), Variable("2", Int, 2) });
	assert(Operation<bool>(eq, Expressions({ "1", "+", "3", "/", "2" }, &temp5).Eval(), 1 + 3.0 / 2));

	//1.0 + 3 / 2 == 2
	VariablesVec temp6({ Variable("1", Float, 1), Variable("3", Int, 3), Variable("2", Int, 2) });
	assert(Operation<bool>(eq, Expressions({ "1", "+", "3", "/", "2" }, &temp6).Eval(), 1.0 + 3 / 2));

	//longer stuff now:
	//4 * 2.0 / 5 == 1.6
	VariablesVec temp7({ Variable("4", Float, 4), Variable("2.0", Float, 2), Variable("5", Float, 5) });
	assert(Operation<float>(eq, Expressions({ "4", "*", "2.0", "/", "5" }, &temp7).Eval(), 4 * 2.0 / 5));

}

void QExpressions::MakeLiteralExpression(int max,		//maximum operand value
										int minOperands)	//minimum number of terms
{
	//the number of operands in the equation
	int numOperands = GenerateRand<int>(minOperands, minOperands + 2);

	int tempId = GenerateRand<int>(0, IDENTIFIERS.size() - 1);	//the assigned variable in the question

	VariablesVec* var;

	//if it is a small expression, include a variable
	if (numOperands < 4)
	{
		var = new VariablesVec({ Variable(IDENTIFIERS[(tempId + 1) % IDENTIFIERS.size()], Int, GenerateRand<float>(2, max)) });
	}
	else
	{
		var = NULL;
	}

	//generate the expression using the constructor:
	Expressions expr(numOperands, max, var, add, mod);

	float tempCorrect;				//the correct value
	vector<float> tempWrong(wrong.size(), 0);	//the wrong answers

	tempCorrect = expr.Eval();
	
	tempWrong[0] = expr.EvalNoOrder(); //no order of ops
	tempWrong[1] = expr.EvalNoOrder(false); //all float types
	tempWrong[2] = expr.EvalNoOrder(true, true); //backwards
	tempWrong[3] = expr.EvalNoOrder(false, true); //all float types backwards

	CheckUniqueAnswers<float, float>(tempCorrect, tempWrong, 2); //guarantees 2 decimal places

	//Writing the question to the file.

	prompt += "Solve the following problem: \n<pre>";

	//print the variable (if there is one)
	if (var != NULL)
	{
		prompt += var->Print();

		//then delete it
		delete var;
	}

	prompt += "int " + IDENTIFIERS[tempId] + " = " + expr.Print() + ";</pre>\n";

	prompt += "What is the variable \"" + IDENTIFIERS[tempId] + "\" equal to?\n";

	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i], tempWrong[i] > 1000); //the last argument makes the value fixed if it is over 1000
																	 //SIDE NOTE: WHY SHOULD THERE EVERY BE ANSWERS APPEARING IN SCIENTIFIC NOTATION THATS CRAZY ASKJDFHAKL;SJDFHLAKSJD
																	// TODO: confirm if this still occurrs
	}

	correct = FloatToString(tempCorrect);
}

void QExpressions::TypeOne() {
	int max = 5;
	int minOperands = 2;
	MakeLiteralExpression(max, minOperands);
}

void QExpressions::TypeTwo() {
	int max = 7;
	int minOperands = 3;
	MakeLiteralExpression(max, minOperands);
}

void QExpressions::TypeThree() {
	int max = 10;
	int minOperands = 4;
	MakeLiteralExpression(max, minOperands);
}

void QExpressions::TypeFour() {
	int max = 12;
	int minOperands = 5;
	MakeLiteralExpression(max, minOperands);
}