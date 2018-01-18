
#include "Expressions.h"


//TODO:
// 1) implement parentheses generation
// 2) implement support for different operand type generation (and maybe heterogeneous types)

Expressions::Expressions(unsigned int numOperands, int maxVal, VariablesVec* vars, Symbols minOperator, Symbols maxOperator, bool differentExpressionOrder, bool parentheses)
{
	assert(minOperator < maxOperator);

	if (vars != NULL)
	{
		variables.Copy(*vars, false);
	}

	//include any literals if there aren't enough variables:
	unsigned int originalSize = variables.Size();
	for (unsigned int i = 0; i < (numOperands - originalSize); i++)
	{
		int temp = GenerateRand<int>(2, maxVal);

		//TODO: allow more datatypes (maybe need extra parameter?)
		variables.AddVariable(Variable(FloatToString(temp), Int, (float)temp), false); //just int for now
	}

	if (differentExpressionOrder)
	{
		//randomize the order of the variables
		variables.Randomize();
	}

	//initialize the expression:
	expression.push_back(variables.GetVariable(0).id);

	//initialize for loop:
	Symbols oldSymb = GenerateRand<Symbols>(minOperator, maxOperator);
	Symbols newSymb;

	for (int i = 1; i < numOperands; i++)
	{
		//generate a new operator (different from the last one)
		do
		{
			newSymb = GenerateRand<Symbols>(minOperator, maxOperator);
		} while (newSymb == oldSymb);
		
		expression.push_back(SYMBOLS[newSymb]);

		//and a new operand:
		expression.push_back(variables.GetVariable(i).id);

		oldSymb = newSymb;
	}
	
}

Expressions::Expressions(vector<string> exp, VariablesVec* vars, bool uniqueIds, bool forceType) : expression(exp)
{
	if (vars != NULL)
	{
		variables.Copy(*vars, uniqueIds, forceType);
	}
}

vector<string> Expressions::GetExpr()
{
	return expression;
}


string Expressions::Print()
{
	string res = "";

	for (size_t i = 0; i < expression.size() - 1; i++)
	{
		res += expression[i];

		if (expression[i] != "(" && expression[i + 1] != ")" && expression[i + 1] != "++")
		{
			res += " ";
		}
	}

	res += expression.back();

	return res;
}

VariablesVec Expressions::GetVariables()
{
	return variables;
}

void Expressions::RandomizeVariablesDefinition()
{
	variables.Randomize();
}

//NOTE: should this be a templated return?
float Expressions::Eval()
{
	vector<Variable> stack;		//a stack for operands and their datatypes

	//generate postfix expression first:
	if (postfix.size() == 0)
	{
		MakePostfix();
	}

	//then perform calculations:
	for (string i : postfix)
	{
		//this is an integer literal or variable name (both are stored in variables)
		if (isdigit(i[0]) || isalpha(i[0]))
		{
			stack.push_back(variables.GetVariable(i));
		}
		else
		{
			Variable temp1, temp2;

			temp2 = stack.back();
			stack.pop_back();

			temp1 = stack.back();
			stack.pop_back();

			//find the index of the given symbol (so we can use the enumerated value):
			int index = find(SYMBOLS.begin(), SYMBOLS.end(), i) - SYMBOLS.begin();

			float newVal = Operation((Symbols)index, temp1.val, temp1.type, temp2.val, temp2.type);

			stack.push_back(Variable(FloatToString(newVal), max(temp1.type, temp2.type), newVal));
		}
	}

	//make sure the calculations went alright 
	assert(stack.size() == 1);

	return stack.back().val;
}

float Expressions::EvalNoOrder(bool useTypes, bool backwards)
{
	vector<float> operands;
	vector<DataTypes> types;
	vector<Symbols> operators;

	vector<string> tempExpr = expression;

	if (backwards)
	{
		reverse(tempExpr.begin(), tempExpr.end());
	}

	for (string i : tempExpr)
	{
		if (i == "(" || i == ")" || i == "++")
		{
			continue;
		}
		else if (isdigit(i[0]) || isalpha(i[0]))
		{
			//perform the calculation
			if (operands.size() == 1)
			{
				float temp1 = operands.back();
				operands.pop_back();
				DataTypes type1 = types.back();
				types.pop_back();

				Symbols op = operators.back();
				operators.pop_back();

				DataTypes type2 = variables.GetVariable(i).type;
			
				operands.push_back(Operation(op, temp1, type1, variables.GetVariable(i).val, type2));
				types.push_back(max(type1, type2));
			}
			//push to stack
			else
			{
				operands.push_back(variables.GetVariable(i).val);
				if (useTypes)
				{
					types.push_back(variables.GetVariable(i).type);
				}
				else
				{
					types.push_back(Float);
				}
			}
		}
		else
		{
			//add to the operator stack
			int temp = find(SYMBOLS.begin(), SYMBOLS.end(), i) - SYMBOLS.begin();
			operators.push_back((Symbols)temp);
		}
	}

	assert(operands.size() == 1);
	return operands.back();
}

/* GRAMMAR:
	NOTE: this needs to include a postfix unary operator of "++"

<E> -> <A> {|| <A>}
<A> -> <B> {&& <A>}
<B> -> <C> {(== | !=) <C>}
<C> -> <D> {(> | >= | < | <=) <D>}
<D> -> <T> {(+ | -) <T>}
<T> -> <F> {(* | / | %) <F>}
<F> -> id | literal | ( <E> )

*/

//private
void Expressions::MakePostfix()
{
	int currentToken = 0; //this is an index for the current token being parsed ([0, expression.size() - 1])
	E(currentToken);
}

void Expressions::E(int& currentToken)
{
	A(currentToken);

	string tempOp = expression[currentToken];

	while (tempOp == "||")
	{
		//move on to next token
		currentToken++;
		A(currentToken);

		//and push the old operator (after T has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::A(int& currentToken)
{
	B(currentToken);

	string tempOp = expression[currentToken];

	while (tempOp == "&&")
	{
		//move on to next token
		currentToken++;
		B(currentToken);

		//and push the old operator (after T has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::B(int& currentToken)
{
	C(currentToken);

	string tempOp = expression[currentToken];

	while (tempOp == "==" || tempOp == "!=")
	{
		//move on to next token
		currentToken++;
		C(currentToken);

		//and push the old operator (after T has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::C(int& currentToken)
{
	D(currentToken);

	string tempOp = expression[currentToken];

	while (tempOp == ">" || tempOp == ">=" || tempOp == "<" || tempOp == "<=")
	{
		//move on to next token
		currentToken++;
		D(currentToken);

		//and push the old operator (after T has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::D(int& currentToken)
{
	T(currentToken);

	string tempOp = expression[currentToken];

	while (tempOp == "+" || tempOp == "-")
	{
		//move on to next token
		currentToken++;
		T(currentToken);

		//and push the old operator (after T has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::T(int& currentToken)
{
	F(currentToken);
	
	string tempOp = expression[currentToken];

	while (tempOp == "*" || tempOp == "/" || tempOp == "%")
	{
		//move on to next token
		currentToken++;
		F(currentToken);

		//and push the old operator (after F has pushed its contents)
		postfix.push_back(tempOp);
		tempOp = expression[currentToken];
	}
}

void Expressions::F(int& currentToken)
{
	//if the first character of the current lexeme (or token) is an alpha character
	//or a digit, we can simply add it to the postfix expression
	if (isalpha(expression[currentToken][0]) || isdigit(expression[currentToken][0]))
	{
		postfix.push_back(expression[currentToken]);
	}
	//else its another expression with parenthesis
	else
	{
		assert(expression[currentToken] == "(");
		currentToken++;
		E(currentToken);
		assert(expression[currentToken] == ")");
	}

	//move on to the next lexeme in the expression
	currentToken++;

	//if we've reached the end of the expression, set the currentToken to 0 (which is guaranteed to not be an operator)
	//this is kind of a hacky way to end the parsing process.
	if (currentToken >= expression.size())
	{
		currentToken = 0;
	}
}