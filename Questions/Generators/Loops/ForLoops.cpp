#include "ForLoops.h"

//===============================================================================================
//========================================ForLoops Class===================================
//===============================================================================================

string ForLoops::Print(string id, string body)
{
	//first the for loop declaration
	string res = "for (int " + id + " = " + to_string(start) + "; " + id + " " + SYMBOLS[compSymb] + " "
		+ to_string(stop) + "; " + id + " = " + id + " " + SYMBOLS[incSymb] + " " + to_string(increment) + ")\n";

	//then the body:
	res += "\\{\n";

	char* cBody = _strdup((char*)body.c_str());
	char * token, * nextToken;

	token = strtok_s(cBody, "\n", &nextToken);
	while (token != NULL)
	{
		res += "\t" + string(token) + "\n";
		token = strtok_s(NULL, "\n", &nextToken);
	}

	res += "\\}\n";

	free(cBody);

	return res;
}



void ForLoops::Tests()
{
	
}
