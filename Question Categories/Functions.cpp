
#include "question.h"
#include "Functions.h"

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

void Functions::TypeOne() 
{
	int num_parameters = 3;					//number of parameters in function header
	int num_vars = 3;						//number of variables declared in main program
	
	bool differentExpressionOrder = false;

	int typeRange = Int;			//a range to go from 0 to typeRange
	int operatorRange = sub;		//and by the same logic as above, gives a range of 0 to n of what operators to use (see SYMBOLS)

	int ref = GenerateRand<int>(0, num_parameters);		//choose the element we are referencing (i.e. which one is assigned in the function)
	
	//use a datastructure defined in quetsion.h
	Variables mainScope(num_vars);
	Parameters funcScope(num_parameters);
	vector<Symbols> operators(num_parameters - 1);	//indicies of the symbols in the functional expression
	
	//------------------------------------------------------------------
	//-------------------INITIALIZE ALL VALUES--------------------------
	//------------------------------------------------------------------
	
	//build the basic structure of the parameters (ids, datatypes, etc.)
	for (int i = 0; i < funcScope.size; i++)
	{
		funcScope.ids[i] = ALPHA_LETTERS[i];
		funcScope.dataTypes[i] = GenerateRand<DataTypes>(0, typeRange + 1); //add one to account for %
		funcScope.refs[i] = GenerateRand<int>(0, 2) == 1; //and determine if they are reference
	}
	
	//then randomize them 
	random_shuffle(funcScope.order.begin(), funcScope.order.end());
	funcScope.ReorderStructure();

	//and initialize the operators now
	for (size_t i = 0; i < operators.size(); i++)
	{
		do
		{
			operators[i] = GenerateRand<Symbols>(0, operatorRange + 1);
		} while (i > 0 && operators[i] == operators[i - 1]);	//do this to get some different operators
	}
	
	//use temporary array to make unique indicies for identifiers
	vector<int> temp_indices(mainScope.size, -1);

	for (int i = 0; i < mainScope.size; i++)
	{
		temp_indices[i] = FindUnique(temp_indices, i, IDENTIFIERS.size());
		mainScope.ids[i] = IDENTIFIERS[temp_indices[i]];	//assign unique id												
		mainScope.vals[i] = GenerateRand<float>(1, 11);		//range of operand values
		mainScope.dataTypes[i] = Int;						//only use ints for now	
	}

	//------------------------------------------------------------------
	//--------------------PRINT THE QUESTION----------------------------
	//------------------------------------------------------------------

	//NOTE: it is important to know that if differentExpressionOrder is true,
	//the order of funcScope ids and vals will match the functional expression
	//BUT, the datatypes and references will match the original order (the same
	//order as the funciton signature). This is good because we use ref like that in 
	//ReturnReferenceParameter
	prompt += PrintVoidFunction(mainScope, funcScope, operators, ref, differentExpressionOrder);

	//------------------------------------------------------------------
	//-------------------CALCULATE THE ANSWER---------------------------
	//------------------------------------------------------------------
	vector<float> tempWrong(wrong.size());

	//this function returns the value of the parameter at ref after the function
	//and assigns some wrong answers
	//be sure to follow preconditions!
	float tempCorrect = ReturnReferenceParam(mainScope, funcScope, operators, ref, tempWrong);

	//check and make sure the answers are unique:
	CheckUniqueAnswers<float, float>(tempCorrect, tempWrong); 

	//now print answers:
	for (size_t i = 0; i < wrong.size(); i++)
	{
		wrong[i] = FloatToString(tempWrong[i]);
	}

	correct = FloatToString(tempCorrect);
}

void Functions::TypeTwo()
{
	int num_params = 2;	//number of parameters
	int max = 10;		//max value for operands
	bool differentExpressionOrder = false;
	
	DataTypes returnType = GenerateRand<DataTypes>(0, Void + 1);
	int funcName = GenerateRand<int>(0, IDENTIFIERS.size());

	//variables used for answer calculation:
	float tempCorrect;
	vector<float> tempWrong(2);
	
	Parameters params(num_params);		
	vector<Symbols> operators(num_params - 1);
	
	//a temporarily used vector to find unique string for ids
	vector<int> temp_ids(params.size);

	for (int i = 0; i < params.size - 1; i++)
	{
		params.dataTypes[i] = GenerateRand<DataTypes>(0, Void); //use every datatype except void
		params.vals[i] = GenerateRand<float>(0.5, max, 2);		//use min of 0.5 because we aren't checking for / 0 errors

		params.refs[i] = false;	//right now, we don't want any reference because we pass literals (and extra logic is needed for multiple datatypes)

		temp_ids[i] = FindUnique(temp_ids, i, IDENTIFIERS.size());
		
		params.ids[i] = IDENTIFIERS[temp_ids[i]];

		//operator values:
		do
		{
			operators[i] = GenerateRand<Symbols>(0, sub + 1);
		} while (operators[i] == mod);	//just don't do % for these because of problems with float
										//maybe i should push the index for % further back
	}

	//and find one last id:
	params.ids[params.size - 1] = IDENTIFIERS[FindUnique(temp_ids, params.size - 1, IDENTIFIERS.size())];
	
	//assign last param type to be different from the return type:
	if (returnType != Float)
	{
		params.dataTypes[params.size - 1] = Float;
	}
	else
	{
		params.dataTypes[params.size - 1] = Int;
	}
	
	//last param value:
	params.vals[params.size - 1] = GenerateRand<float>(0.5, max, 2);

	prompt += PrintFunctionHeader(returnType, funcName, params);
	
	//change the order if specified:
	if (differentExpressionOrder)
	{
		random_shuffle(params.order.begin(), params.order.end());

		params.Variables::ReorderStructure(params.ids);
	}

	prompt += "\\{\n\treturn ";

	prompt += PrintExpr(params.ids, operators);
	
	prompt += "\\}\n";

	//MAYBE OVERLOAD THE PRINTFUNCTIONCALL TO INCLUDE LITERAL VALUES LIKE THIS
	
	prompt += "int main()\n\\{\n\tcout << " + FUNCTION_IDS[funcName] + "(";

	for (int i = 0; i < params.size; i++)
	{
		//just use the literal values we've already generated
		//with the decimal point
		prompt += FloatToString(params.vals[i], true, 1) + ", ";
	}

	prompt.replace(prompt.end() - 2, prompt.end(), ");\n\treturn 0; \n\\}</pre>\n");
	
	//make a wrong answer before we convert the paramters:
	tempWrong[0] = EvalExpr<float>(params.vals, operators);

	tempCorrect = Convert(returnType, PassAndEvalFunc(params, params.vals, operators));

	tempWrong[1] = EvalExpr(params.vals, params.dataTypes, operators, false);

	CheckUniqueAnswers(tempCorrect, tempWrong);

	if (returnType == Void)
	{
		correct = "Compile-time error";
		wrong[0] = FloatToString(tempCorrect);
	}
	else
	{
		correct = FloatToString(tempCorrect);
		wrong[0] = "Compile-time error";
	}	

	wrong[1] = "Run-time error";
	wrong[2] = FloatToString(tempWrong[0]);
	wrong[3] = FloatToString(tempWrong[1]);
}

void Functions::TypeThree() 
{


}

void Functions::TypeFour()
{
	
}

//ADD THE PRECONDITION THAT THE PARAM DATATYPES ARE IN THE ORIGINAL ORDER
//AND IF THE ORDER OF VARIABLES HAS BEEN CHANGED FOR AN EXPRESSION, THEN IT IS STORED IN order()
float Functions::PassAndEvalFunc(Parameters& params, vector<float> vals, vector<Symbols> operators)
{
	float tempCorrect;
		
	//pass the values
	for (int i = 0; i < params.size; i++)
	{
		params.vals[i] = Convert(params.dataTypes[i], vals[i]); //NOTE: FOR THIS TO BE TRUE, THE ORDER OF THE DATATYPES MUST BE RESERVED
	}
		
	//reorder to the order of the expression
	params.Variables::ReorderStructure(params.vals);
		
	tempCorrect = EvalExpr(params.vals, params.dataTypes, operators);	//don't convert the answer though, that is up to the callee
		
	return tempCorrect;
}

string Functions::PrintFunctionHeader(int returnType,			//index for a returnType in RETURN_TYPES[]
								   	  int funcName,				//index for function name in FUNCTION_IDS[]
								   	  const Parameters& params)	//contains the ids and if the parameters are reference
{
	string res = "What values are printed out at the end of the code?\n";

	res += "<pre>";
	res += DATA_TYPES[returnType] + " " + FUNCTION_IDS[funcName] + "(";
	
	for (int i = 0; i < params.size; i++)
	{
		//and print them to the question:
		res += DATA_TYPES[params.dataTypes[i]];

		//if the parameter is a reference parameter
		if (params.refs[i])
		{
			res += "&";
		}

		res += " " + params.ids[i] + ", ";
	}

	//give the last identifier proper format:
	//NOTE: if we wish to change to functions with no params like Print(), we need to change this somehow
	res.replace(res.end() - 2, res.end(), ")\n");
	
	return res;
}

string Functions::PrintFunctionCall(const int& functionIndex, const vector<string>& ids)
{
	string res = "\t" + FUNCTION_IDS[functionIndex] + "(";

	for (size_t i = 0; i < ids.size(); i++)
	{
		//pass the ids
		res += ids[i] + ", ";
	}

	res.replace(res.end() - 2, res.end(), ");\n");

	return res;
}

string Functions::PrintVoidFunction(Variables mainScope, 			//the variables declared in the main scope
									Parameters& funcScope, 			//the function parameters
									vector<Symbols> operators, 		//the operators used in the function expression
									int ref, 						//the index of the variable assigned in the function
									bool differentExpressionOrder)	//the option to change up the order of expression and passing of variables
{
	string res = "";
	
	int functionId = GenerateRand<int>(0, FUNCTION_IDS.size());

	//function is always void for this question type
	res += PrintFunctionHeader(Void, functionId, funcScope);

	//now print a single statement of assigenment (e.g. a = c - a * b)
	res += "\\{\n\t" + funcScope.ids[ref] + " = ";

	//and if we want a different order for the expression
	if (differentExpressionOrder)
	{
		//make a new random order for the expression
		random_shuffle(funcScope.order.begin(), funcScope.order.end());

		//reorder the ids to get a different expression
		//NOTE: IT IS IMPORTANT NOW THAT THE REFERENCES DO NOT CHANGE BECAUSE THEY ARE USED WITH ref
		funcScope.Variables::ReorderStructure(funcScope.ids);
	}

	res += PrintExpr(funcScope.ids, operators) + "\\}\n";

	//print main() template:
	res += "int main()\n\\{\n";

	for (int i = 0; i < mainScope.size; i++)
	{
		//print out too:
		res += "\t" + DATA_TYPES[mainScope.dataTypes[i]] + " " + mainScope.ids[i] + " = " + FloatToString(mainScope.vals[i]) + ";\n";
	}

	if (differentExpressionOrder)
	{
		//randomize the main variable structure to pass to the question "function"
		random_shuffle(mainScope.order.begin(), mainScope.order.end());
		mainScope.ReorderStructure();
	}

	//print the function call
	//NOTE: this currently assumes that mainScope.size == funcScope.size
	//if we wish to change that, we would add another parameter
	assert(mainScope.size == funcScope.size);
	res += PrintFunctionCall(functionId, mainScope.ids);

	res += "\tcout << " + mainScope.ids[ref] + " << endl;\n\treturn 0;\n\\}</pre>";

	return res;
}

float Functions::ReturnReferenceParam(Variables mainScope, 		//values of the arguments
									 Parameters funcScope, 		//order and reference of the parameters; NOTE: must meet preconditions of PassAndEvalFunc
									 vector<Symbols> operators, //operators used in function
									 int ref, 					//the index of the parameter being assigned
									 vector<float>& tempWrong)	//a return vector for wrong answers
{
	//this function passes the values to the function, then executes the expression
	//based on the order in funcScope and the operators.
	//it returns the value of the expression
	float tempCorrect = Convert(mainScope.dataTypes[ref], PassAndEvalFunc(funcScope, mainScope.vals, operators));
	
	//should have 4 wrong answers for this question
	assert(tempWrong.size() == 4);
	tempWrong[0] = mainScope.vals[ref];
	tempWrong[1] = EvalExpr<float>(funcScope.vals, operators, false); //this disregards order of operations
	tempWrong[2] = float(funcScope.vals[(ref + 1) % funcScope.size]);
	tempWrong[3] = EvalExprBackwards<float>(funcScope.vals, operators);
	
	//and change the answer if it was pass-by-value
	if (!funcScope.refs[ref])
	{
		tempWrong[0] = tempCorrect;
		tempCorrect = mainScope.vals[ref];
	}
	
	return tempCorrect;
}

void Functions::Tests()
{
	//And notes on testing:
	//I find it kind of hard to make an exact function that tests how each "question function" executes and
	//how it treats reference paramters and all that. It seems this would be easier to test in something
	//like python where I can pass functions as objects and use eval(). Right now, I'm not going to try and
	//implement tests for this class, just keep that in mind for the future
	
	//TypeOne() testing
	//checking if reference parameter is returned properly
	
	vector<float> tempWrong(4);
	//all of these questions use exlusively int datatype for now:
	vector<DataTypes> types = {Int, Int, Int};
	vector<string> ids = {"", "", ""};
	vector<float> unusedVals = {0, 0, 0};	//this is used to initialize the parameters
	vector<float> vals = {1, 7, 3};			//this is used for answer calculations
	vector<Symbols> ops = {sub, divide};
	int right = 1 - 7 / 3; //a particular expression used for testing
	
	//loop through each position
	//only testing for size 3
	//there are total of 24 combinations of reference variables and reference values
	//that's 2**3 options for reference variables * 3 options for the reference index
	//there's 12 cases covered here
	for (size_t i = 0; i < vals.size(); i++)
	{
		//no references in each spot:
		assert(ReturnReferenceParam(Variables(types, vals, ids), Parameters(types, unusedVals, ids, { false, false, false }), ops, i, tempWrong) == vals[i]);
		//references in every spot:
		assert(ReturnReferenceParam(Variables(types, vals, ids), Parameters(types, unusedVals, ids, {true, true, true}), ops, i, tempWrong) == right);
		//references only in the spot of the referenced variable:
		assert(ReturnReferenceParam(Variables(types, vals, ids), Parameters(types, unusedVals, ids, {i == 0, i == 1, i == 2}), ops, i, tempWrong) == right);
		//references in every spot BUT of the referenced variable:
		assert(ReturnReferenceParam(Variables(types, vals, ids), Parameters(types, unusedVals, ids, {i != 0, i != 1, i != 2}), ops, i, tempWrong) == vals[i]);
	}
	
	
	//test type two just by testing a combination of Convert and PassAndEvalFunc:
	//separate each by return type
	//so one for void, one for int, one for float
	//then for int and for float, make one each for the data types
	//thats (int, int), (int, float), (float, int), (float, float)
	//and use some vaules that truncate at each step
	//like 2.5 / 3.5
	
	//only test questions of type 2
	//with these different combination of datatypes:
	//{{Int, Int}, {Int, Float}, {Float, Int}, {Float, Float}}
	
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
}