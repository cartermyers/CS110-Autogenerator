
#include "question.h"
#include "QFunctions.h"

//*******************************************************************************************
//							FUNCTIONS SUBCLASS DEFINITIONS	
//
//*******************************************************************************************

//NOTE FOR FUTURE CONSIDERATION:
//currently, this question only uses variables as int
//but if we decide to use a mixed datatype thing
//where the parameters have multiple datatypes, and so do the
//main scope variables, there needs to be some logic 
//to make sure that:
//if a parameter is pass-by-reference, the argument passed to it must be of the same datatype
//otherwise there is a compiler error
//however, pass-by-value parameters may have different datatypes than their arguments

void QFunctions::TypeOne() 
{

	int num_parameters = 3;					//number of parameters in function header
	int num_vars = 3;						//number of variables declared in main program
	
	bool differentExpressionOrder = false;

	int minType = Int;
	int maxType = Int;			//a range to go from 0 to typeRange

	Symbols minOperator = add;		//and by the same logic as above, gives a range of 0 to n of what operators to use (see SYMBOLS)
	Symbols maxOperator = mod;

	int minVal = 2;
	int maxVal = 5;

	int ref = GenerateRand<int>(0, num_parameters - 1);		//choose the element we are referencing (i.e. which one is assigned in the function)
	
	VariablesVec mainScope;

	//------------------------------------------------------------------
	//-------------------INITIALIZE ALL VALUES--------------------------
	//------------------------------------------------------------------

	//use temporary array to make unique indicies for identifiers
	vector<int> temp_indices(num_vars, -1);

	for (int i = 0; i < num_vars; i++)
	{
		temp_indices[i] = FindUnique(temp_indices, i, IDENTIFIERS.size() - 1);
		mainScope.AddVariable(Variable(IDENTIFIERS[temp_indices[i]], GenerateRand<DataTypes>(minType, maxType), GenerateRand<float>(minVal, maxVal)));
	}

	//then generate the function (with using the variables as a base point for the parameters)
	// and use the same datatypes for the parameters
	// it also passes the values over to the parameters
	Functions funcScope(Void, FUNCTION_IDS[GenerateRand<int>(0, FUNCTION_IDS.size() - 1)], &mainScope);

	//and alter the variable position if needed:
	//NOTE: this may cause issues if datatypes are nonhomogeneous
	if (differentExpressionOrder)
	{
		mainScope.Randomize();
	}

	funcScope.PassVariables(mainScope);

	//and initialize the assignment statement in the function (using the parameters we just generated)
	Expressions refAssignment(num_parameters, 0, &(funcScope.GetParameters()), minOperator, maxOperator, differentExpressionOrder);

	//------------------------------------------------------------------
	//--------------------PRINT THE QUESTION----------------------------
	//------------------------------------------------------------------

	prompt += "Given the following function definition:\n";

	prompt += "<pre>";

	// first, get the id of the parameter we are assigning, then assign the expression to it
	string funcBody = funcScope.GetParameters().GetVariable(ref).id + " = " + refAssignment.Print() + ";";

	//and print the above in the function definition
	prompt += funcScope.PrintDefinition(funcBody);

	prompt += "</pre>\n";

	prompt += "What value is printed after the following statments?\n";

	prompt += "<pre>";
	//with the variable declarations
	prompt += mainScope.Print();

	//and the function call:
	prompt += funcScope.PrintCall(mainScope) + ";\n";

	//and the final print statement of the referenced variable:
	prompt += "cout << " + mainScope.GetVariable(ref).id + " << endl;</pre>\n";


	//------------------------------------------------------------------
	//-------------------CALCULATE THE ANSWER---------------------------
	//------------------------------------------------------------------

	vector<float> tempWrong(wrong.size());
	float tempCorrect;
	
	tempCorrect = EvalAndReturnReferenceParam(mainScope, funcScope, refAssignment, ref, tempWrong);

	//check and make sure the answers are unique:
	CheckUniqueAnswers<float, float>(tempCorrect, tempWrong); 

	//now print answers:
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i]);
	}

	correct = FloatToString(tempCorrect);
}

void QFunctions::TypeTwo()
{
	int num_params = 2;	//number of parameters
	int max = 5;		//max value for operands
	bool differentExpressionOrder = false;

	Symbols minOperator = add;
	Symbols maxOperator = divide;

	//use every datatype except void 
	DataTypes minType = Int;
	DataTypes maxType = Float;
	
	DataTypes returnType = Float;	//always use float for this type

	//and never use reference parameters:
	vector<bool> refs(num_params, false);

	//variables used for answer calculation:
	float tempCorrect;
	vector<float> tempWrong(wrong.size());
	
	VariablesVec params;
	//TODO: change uniqueIds to false below
	VariablesVec literals;	//a vector identitcal to the params vector, but the ids are the literal values
	
	//a temporarily used vector to find unique string for ids
	vector<int> temp_ids(num_params);

	for (int i = 0; i < num_params; i++)
	{
		Variable tempVar;
		do
		{
			tempVar.type = GenerateRand<DataTypes>(minType, maxType); 
		} while (i > 0 && tempVar.type == params.GetVariable(i - 1).type);	//and thats different from the previous datatype

		do
		{
			tempVar.val = GenerateRand<float>(2, max, 2);
		} while (i > 0 && Operation<bool>(eq, tempVar.val, literals.GetVariable(i - 1).val));	//and use some different values

		temp_ids[i] = FindUnique(temp_ids, i, IDENTIFIERS.size() - 1);
		tempVar.id = IDENTIFIERS[temp_ids[i]];

		//if a number ends in 0.5 (and is Float), only allow addition and subtraction:
		if ((maxOperator == divide) && ((int)(Convert(tempVar.type, tempVar.val) / 0.5f) % 2 == 1))
		{
			maxOperator = sub;
		}

		params.AddVariable(tempVar);

		//and change the id to the literal value for the literals vector:
		tempVar.id = FloatToString(tempVar.val, true, 1);

		literals.AddVariable(tempVar, false, false);
	}

	//and create function and expression:
	Functions func(returnType, FUNCTION_IDS[GenerateRand<int>(0, FUNCTION_IDS.size() - 1)], &params, refs, false);

	//and pass to the function:
	func.PassVariables(params, true);

	Expressions expr(num_params, 0, &func.GetParameters(), minOperator, maxOperator, differentExpressionOrder);

	//now create an expression for wrong answer generation:
	vector<string> literalExpression = expr.GetExpr();
	int currentLiteral = 0;
	for (size_t i = 0; i < literalExpression.size(); i++)
	{
		if (isalnum(literalExpression[i][0]))
		{
			//substitute all variables for their original literal value:
			literalExpression[i] = literals.GetVariable(currentLiteral++).id;
		}
	}
	//and initialize a new expression with the values:
	Expressions wrongExpr(literalExpression, &literals, false, false);

	//then print: 
	prompt += "Given the following function definition:\n";

	prompt += "<pre>";
	prompt += func.PrintDefinition("return " + expr.Print() + ";");
	prompt += "</pre>\n";

	prompt += "What is printed from the following call?\n";

	prompt += "<pre>";
	prompt += "cout << " + func.PrintCall(literals) + " << endl;\n";
	prompt += "</pre>\n";

	tempCorrect = Convert(returnType, expr.Eval());

	//TODO: make a function that is easily able to use float only operations
	tempWrong[0] = wrongExpr.EvalNoOrder(false, false);
	tempWrong[1] = wrongExpr.EvalNoOrder(false);
	tempWrong[2] = expr.EvalNoOrder(false, true);
	tempWrong[3] = Convert(Int, tempCorrect);

	CheckUniqueAnswers(tempCorrect, tempWrong);

	correct = FloatToString(tempCorrect);

	for (size_t i = 0; i < tempWrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i]);
	}
}

void QFunctions::TypeThree() 
{
	int max = 5;		//max value for operands

	Symbols minOperator = add;
	Symbols maxOperator = divide;

	//use every datatype for return 
	DataTypes returnType = GenerateRand<DataTypes>(Int, Void);	

	//variables used for answer calculation:
	float tempCorrect;
	vector<float> tempWrong(2);

	int numOperands = 2;
	VariablesVec operands;	//operands used in the function expression

	for (int i = 0; i < numOperands; i++)
	{
		Variable tempVar;
		
		tempVar.type = Float;	//always use float for the operands

		do
		{
			tempVar.val = GenerateRand<float>(2, max, 2);		//use min of 0.5 because we aren't checking for / 0 errors
		} while (i > 0 && Operation<bool>(eq, tempVar.val, operands.GetVariable(i - 1).val));

		//and change the id to the literal value:
		tempVar.id = FloatToString(tempVar.val, true, 1);

		operands.AddVariable(tempVar, false, true);
	}

	Functions func(returnType, FUNCTION_IDS[GenerateRand<int>(0, FUNCTION_IDS.size() - 1)]);

	Expressions funcExpr(2, 0, &operands);

	//then print: 
	prompt += "Given the following function definition:\n";

	prompt += "<pre>";
	prompt += func.PrintDefinition("return " + funcExpr.Print() + ";");
	prompt += "</pre>\n";

	prompt += "What is printed from the following call?\n";

	prompt += "<pre>";
	prompt += "\tcout << " + func.PrintCall() + " << endl;\n";
	prompt += "</pre>\n";

	tempWrong[0] = Convert(Float, funcExpr.EvalNoOrder(false, true));

	if (returnType == Void)
	{
		tempCorrect = Convert(Float, funcExpr.Eval());

		tempWrong[1] = Convert(Int, funcExpr.Eval());

		CheckUniqueAnswers(tempCorrect, tempWrong);

		correct = "Compile-time error.";
		wrong[3] = FloatToString(tempCorrect);
	}
	else
	{
		tempCorrect = Convert(returnType, funcExpr.Eval());

		//this wrong answer uses the opposite datatype of the return type:
		tempWrong[1] = Convert((DataTypes) (1 - returnType), funcExpr.Eval());

		CheckUniqueAnswers(tempCorrect, tempWrong);

		correct = FloatToString(tempCorrect);
		wrong[3] = "Compile-time error.";
	}

	wrong[2] = "Run-time error.";

	for (size_t i = 0; i < tempWrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i]);
	}
}

void QFunctions::TypeFour()
{
	
}

float QFunctions::EvalAndReturnReferenceParam(VariablesVec mainScope, Functions funcScope, Expressions funcExpr, int ref, vector<float>& tempWrong)
{
	//TypeOne() calculation:

	assert(tempWrong.size() == 4);

	//first, evaluate the expression:
	float res = funcExpr.Eval();
	tempWrong[0] = mainScope.GetVariable(ref).val;

	//then swap the values if the parameter was NOT pass-by-reference
	if (!funcScope.GetRefs()[ref])
	{
		float temp = tempWrong[0];
		tempWrong[0] = res;
		res = temp;
	}

	tempWrong[1] = funcExpr.EvalNoOrder(); //this disregards order of operations
	tempWrong[2] = funcScope.GetParameters().GetVariable((ref + 1) % funcScope.GetParameters().Size()).val;
	tempWrong[3] = funcExpr.EvalNoOrder(true, true);

	return res;
}

void QFunctions::Tests()
{	
	//TypeOne() testing
	//checking if reference parameter is returned properly
	
	//only Int type for now
	VariablesVec mainScope({ Variable("1", Int, 1), Variable("2", Int, 2), Variable("3", Int, 3) });
	Expressions funcExpr({ "1", "+", "2", "-", "3" }, &mainScope);

	//loop through each position of reference
	//only testing for size 3
	//there are total of 24 combinations of reference variables and reference values
	//that's 2**3 options for reference variables * 3 options for the reference index
	//there's 12 cases covered here
	for (size_t i = 0; i < 3; i++)
	{
		vector<float> tempWrong(4);

		//no references in each spot:
		Functions funcScope1(Void, "tempName", &mainScope, { false, false, false });
		funcScope1.PassVariables(mainScope);
		assert(EvalAndReturnReferenceParam(mainScope, funcScope1, funcExpr, i, tempWrong) == mainScope.GetVariable(i).val); //the value of the original variable

		
		//references in every spot:
		Functions funcScope2(Void, "tempName", &mainScope, { true, true, true });
		funcScope2.PassVariables(mainScope);
		assert(EvalAndReturnReferenceParam(mainScope, funcScope2, funcExpr, i, tempWrong) == 0); //the value of the evaluated expression

		//references only in the spot of the referenced variable:
		Functions funcScope3(Void, "tempName", &mainScope, { i == 0, i == 1, i == 2 });
		funcScope3.PassVariables(mainScope);
		assert(EvalAndReturnReferenceParam(mainScope, funcScope3, funcExpr, i, tempWrong) == 0); //the value of the evaluated expression


		//references in every spot BUT of the referenced variable:
		Functions funcScope4(Void, "tempName", &mainScope, { i != 0, i != 1, i != 2 });
		funcScope4.PassVariables(mainScope);
		assert(EvalAndReturnReferenceParam(mainScope, funcScope4, funcExpr, i, tempWrong) == mainScope.GetVariable(i).val); //the value of the original variable
	}
	
	
	//test type two just by testing a combination of Convert, which has already been tested. so we can trust it for now.


	// OLD TESTS
	
	//separate each by return type
	//so one for void, one for int, one for float
	//then for int and for float, make one each for the data types
	//thats (int, int), (int, float), (float, int), (float, float)
	//and use some vaules that truncate at each step
	//like 2.5 / 3.5
	
	//only test questions of type 2
	//with these different combination of datatypes:
	//{{Int, Int}, {Int, Float}, {Float, Int}, {Float, Float}}
	/*
	ops = {divide};
	unusedVals = {-1, -1};
	ids = {"", ""};
	vector<bool> refs = {false, false};
	
	//Int return:
	
	//Int(Int(10.6) / Int(1.5))
	assert(Convert(Int, PassAndEvalFunc(Parameters({Int, Int}, unusedVals, ids, refs), {float(10.6), 1.5}, ops)) == int(int(10.6) / int(1.5)));
	//Int(float(10.5) / Int(2.5))
	assert(Convert(Int, PassAndEvalFunc(Parameters({Float, Int}, unusedVals, ids, refs), {10.5, 2.5}, ops)) == int(float(10.5) / int(2.5)));
	//int(int(4.5) / float(1.5))
	assert(Convert(Int, PassAndEvalFunc(Parameters({Int, Float}, unusedVals, ids, refs), {4.5, 1.5}, ops)) == int(int(4.5) / float(1.5)));
	//int(float(10.1) / float(1.5))
	assert(Convert(Int, PassAndEvalFunc(Parameters({Float, Float}, unusedVals, ids, refs), {float(10.1), 1.5}, ops)) == int(float(10.1) / float(1.5)));
	
	
	//Float return:
	//Float(Int(1.5) / Int(3.5))
	assert(Convert(Float, PassAndEvalFunc(Parameters({Int, Int}, unusedVals, ids, refs), {1.5, 3.5}, ops)) == float(int(1.5) / int(3.5)));
	//Float(float(10.5) / Int(2.5))
	assert(Convert(Float, PassAndEvalFunc(Parameters({Float, Int}, unusedVals, ids, refs), {10.5, 2.5}, ops)) == float(float(10.5) / int(2.5)));
	//Float(int(4.5) / float(1.5))
	assert(Convert(Float, PassAndEvalFunc(Parameters({Int, Float}, unusedVals, ids, refs), {4.5, 1.5}, ops)) == float(int(4.5) / float(1.5)));
	//Float(float(10.1) / float(1.5))
	assert(Convert(Float, PassAndEvalFunc(Parameters({Float, Float}, unusedVals, ids, refs), {float(10.1), 1.5}, ops)) == float(float(10.1) / float(1.5)));
	*/
}