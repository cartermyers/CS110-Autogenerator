#include "WhileLoops.h"

//===============================================================================================
//===========================================WhileLoops Class=================================
//===============================================================================================

string WhileLoops::Print(string id, string body)
{
	//first the counter declaration:
	string res = "int " + id + " = " + to_string(start) + ";\n";

	//then the condition:
	res += "while (" + id + " " + SYMBOLS[compSymb] + " " + to_string(stop) + ")\n";

	//and the body:
	res += "\\{\n";

	char* cBody = _strdup((char*)body.c_str());
	char * token, *nextToken;

	token = strtok_s(cBody, "\n", &nextToken);
	while (token != NULL)
	{
		res += "\t" + string(token) + "\n";
		token = strtok_s(NULL, "\n", &nextToken);
	}

	free(cBody);

	//loop update at bottom of body:
	res += "\t" + id + " " + SYMBOLS[(incSymb)] + "= " + to_string(increment) + ";\n\\}\n";

	return res;
}

void WhileLoops::Tests()
{

}