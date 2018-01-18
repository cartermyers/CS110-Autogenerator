#include "DoLoops.h"

//TODO LOOPS

//===============================================================================================
//===========================================LinearDoLoops Class=================================
//===============================================================================================

int DoLoops::ComputeLoop()
{
	//in a do while loop,
	//we have at least one loop, even if the loop condition is already met
	//else, it's just like a normal for loop
	if (!Operation<bool>(compSymb, start, stop) && 1 >= minIterations)
	{
		return 1;
	}
	else	
	{
		return Loops::ComputeLoop();
	}

	return 0;
}

vector<int> DoLoops::ShowIterations()
{
	vector<int> res;

	int tempStart = start;

	do
	{
		res.push_back(tempStart);
		tempStart = Operation<int>(incSymb, tempStart, increment);
	} while (Operation<bool>(compSymb, tempStart, stop));

	return res;
}

string DoLoops::Print(string id, string body)
{
	//counter declaration:
	string res = "int " + id + " = " + to_string(start) + ";\n";

	//loop body:
	res += "do\n\\{\n";

	char* cBody = _strdup((char*)body.c_str());
	char * token, *nextToken;

	token = strtok_s(cBody, "\n", &nextToken);
	while (token != NULL)
	{
		res += "\t" + string(token) + "\n";
		token = strtok_s(NULL, "\n", &nextToken);
	}

	free(cBody);

	//counter update:
	res += "\t" + id + " = " + id + " " + SYMBOLS[incSymb] + " " + to_string(increment) + ";\n";

	//comparison:
	res += "\\} while (" + id + " " + SYMBOLS[compSymb] + " " + to_string(stop) + ");\n";

	return res;
}


//===============================================================================================
//================================================ Tests ========================================
//===============================================================================================

void DoLoops::Tests()
{		

	// PART ONE
	// only do += and -=


	//check to make sure a couple regular cases work
	// i = 0 i < 4 i += 1
	start = 0; compSymb = lt; stop = 4; incSymb = add; increment = 1;
	assert(ComputeLoop() == 4);
	
	// i = 0 i <= 4 i += 1
	start = 0; compSymb = lte; stop = 4; incSymb = add; increment = 1;
	assert(ComputeLoop() == 5);
	
	// i = 6 i > 2 i -= 1
	start = 6; compSymb = gt; stop = 2; incSymb = sub; increment = 1;
	assert(ComputeLoop() == 4);
	
	// i = 7 i >= 3 i -= 2
	start = 7; compSymb = gte; stop = 3; incSymb = sub; increment = 2;
	assert(ComputeLoop() == 3);
	
	//now only check special cases
	// i = 5 i < 3 i += 2
	start = 5; compSymb = lt; stop = 3; incSymb = add; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 6 i <= 3 i -= 3
	start = 6; compSymb = lte; stop = 3; incSymb = sub; increment = 3;
	assert(ComputeLoop() == 1);
	
	// i = 4 i > 4 i += 1
	start = 4; compSymb = gt; stop = 4; incSymb = add; increment = 1;
	assert(ComputeLoop() == 1);
	
	// i = 0 i >= 3 i += 2
	start = 0; compSymb = gte; stop = 3; incSymb = add; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 5 i <= 4 i += 1
	start = 5; compSymb = lte; stop = 4; incSymb = add; increment = 1;
	assert(ComputeLoop() == 1);


	//	PART TWO
	// now all cases for *= and /=

	//check for a couple of regular cases

	// i = 1 i < 8 i *= 2
	start = 1; compSymb = lt; stop = 8; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 3);
	
	// i = 1 i < 7 i *= 2
	start = 1; compSymb = lt; stop = 7; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 3);
	
	// i = 1 i < 9 i *= 2
	start = 1; compSymb = lt; stop = 9; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 4);
	
	// i = 1 i <= 8 i *= 2
	start = 1; compSymb = lte; stop = 8; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 4);
	
	// i = 7 i > 3 i /= 2
	start = 7; compSymb = gt; stop = 3; incSymb = divide; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 7 i >= 3 i /= 2
	start = 7; compSymb = gte; stop = 3; incSymb = divide; increment = 2;
	assert(ComputeLoop() == 2);
	
	// i = 9 i > 3 i /= 2
	start = 9; compSymb = gt; stop = 3; incSymb = divide; increment = 2;
	assert(ComputeLoop() == 2);
	
	//now only check special cases for Do Loops
	
	// i = 1 i > 1 i /= 2
	start = 1; compSymb = gt; stop = 1; incSymb = divide; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 7 i < 3 i /= 2
	start = 7; compSymb = lt; stop = 3; incSymb = divide; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 8 i > 9 i *= 2
	start = 8; compSymb = gt; stop = 9; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 1);
	
	// i = 8 i > 9 i *= 2
	start = 8; compSymb = gt; stop = 8; incSymb = mul; increment = 2;
	assert(ComputeLoop() == 1);
	
}