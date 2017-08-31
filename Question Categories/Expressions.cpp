//*******************************************************************************************
//							EXPRESSIONS SUBCLASS DEFINITIONS	
//
//*******************************************************************************************

#include "question.h"
#include "Expressions.h"

void Expressions::Tests()
{
	//no need to really test because the main answer function in this class is EvalExpr
	//which is a function of questions, which already has a test section
}

void Expressions::MakeLiteralExpression(int max,		//maximum operand value
										int minTerms)	//minimum number of terms
{
	//the number of operators in the equation
	int num_operators = GenerateRand<int>(minTerms, minTerms + 2);

	float tempCorrect;				//the correct value
	vector<float> tempWrong(wrong.size(), 0);	//the wrong answers

	//think about these questions as all Variables
	//with their ids as literals (i.e. "4")
	Variables expression(num_operators + 1);		//mostly used to represent number of operands, ids, and values
	vector<Symbols> operators(num_operators);		//indices to represent the operators being used

	//generate random values for the expression:
	MakeExpr(expression.vals, operators, max);		
													
	//these questions only contain int operations,
	//so let's be explicit to make sure they are all int
	for (int i = 0; i < expression.size; i++)
	{
		expression.dataTypes[i] = Int;
		
		expression.vals[i] = Convert(Int, expression.vals[i]);
	}

	tempCorrect = EvalExpr(expression.vals, expression.dataTypes, operators);
	tempWrong[0] = EvalExpr<float>(expression.vals, operators);
	tempWrong[1] = EvalExpr<float>(expression.vals, operators, false); //don't use PEDMAS
	tempWrong[2] = float(EvalExpr(expression.vals, expression.dataTypes, operators, false));
	tempWrong[3] = EvalExprBackwards<float>(expression.vals, operators);

	CheckUniqueAnswers<float, float>(tempCorrect, tempWrong, 2); //guarantees 2 decimal places

	//Writing the question to the file.

	prompt += "Solve the following problem: \n";

	prompt += "<pre>";

	int temp = GenerateRand<int>(0, IDENTIFIERS.size()); //random id

	//only use this for small expressions
	if (num_operators < 4)
	{
		expression.ids[0] = IDENTIFIERS[temp];

		prompt += "int " + expression.ids[0] + " = " + FloatToString(expression.vals[0]) + ";\n";
	}
	else
	{
		expression.ids[0] = FloatToString(expression.vals[0]);
	}

	//get the rest of the ids ready for printing:
	for (int i = 1; i < expression.size; i++)
	{
		expression.ids[i] = FloatToString(expression.vals[i]);
	}

	prompt += "int " + IDENTIFIERS[(++temp) % IDENTIFIERS.size()] + " = " + PrintExpr(expression.ids, operators) + "</pre>";

	prompt += "What is the variable \"" + IDENTIFIERS[temp % IDENTIFIERS.size()] + "\" equal to?\n";

	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i], tempWrong[i] > 1000); //the last argument makes the value fixed if it is over 1000
																	 //SIDE NOTE: WHY SHOULD THERE EVERY BE ANSWERS APPEARING IN SCIENTIFIC NOTATION THATS CRAZY ASKJDFHAKL;SJDFHLAKSJD
	}

	correct = FloatToString(tempCorrect);
}

void Expressions::TypeOne() {
	int max = 5;
	int minTerms = 2;
	MakeLiteralExpression(max, minTerms);
}

void Expressions::TypeTwo() {
	int max = 7;
	int minTerms = 3;
	MakeLiteralExpression(max, minTerms);
}

void Expressions::TypeThree() {
	int max = 10;
	int minTerms = 4;
	MakeLiteralExpression(max, minTerms);
}

void Expressions::TypeFour() {
	int max = 12;
	int minTerms = 5;
	MakeLiteralExpression(max, minTerms);
}