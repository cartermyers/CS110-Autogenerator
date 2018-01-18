
#include "Functions.h"

Functions::Functions(DataTypes returnDataType, string functionName, VariablesVec* vars, vector<bool> refParams, bool differentDataTypes, DataTypes minType, DataTypes maxType)
{
	returnType = returnDataType;
	name = functionName;

	if (vars == NULL)
	{
		assert(refParams.size() == 0);
	}
	else
	{
		refs = refParams;

		//generate more refs if needed
		for (int i = refs.size(); i < vars->Size(); i++)
		{
			refs.push_back(GenerateRand<bool>(false, true));
		}

		//now copy over all of the variables (and change their type if permitted)
		for (int i = 0; i < vars->Size(); i++)
		{
			Variable tempVar = vars->GetVariable(i);

			//change the type (if it's not a reference, and new types are allowed)
			if (!refs[i] && differentDataTypes)
			{
				tempVar.type = GenerateRand<DataTypes>(minType, maxType);
			}

			//and change the name (this is non-optional)
			tempVar.id = ALPHA_LETTERS[i];

			//and set the value to -1 (all values should be initialized by the "PassVariables" function)
			tempVar.val = -1;

			//then add to params:
			params.AddVariable(tempVar);
		}
	}
}

void Functions::PassVariables(VariablesVec vars, bool convertType)
{
	assert(vars.Size() == params.Size());

	for (size_t i = 0; i < params.Size(); i++)
	{
		Variable newParam = vars.GetVariable(i);
		Variable oldParam = params.GetVariable(i);

		if (refs[i])
		{
			assert(newParam.type == oldParam.type);
		}

		params.SetVariableVal(i, newParam.val, convertType);
	}
}

string Functions::PrintDefinition(string body)
{
	string res = DATA_TYPES[returnType] + " " + name + "(";

	for (size_t i = 0; i < params.Size(); i++)
	{
		Variable tempVar = params.GetVariable(i);

		res += DATA_TYPES[tempVar.type];

		if (refs[i])
		{
			res += "&";
		}

		res += " " + tempVar.id + ", ";
	}

	//remove last comma and space:
	if (params.Size() > 0)
	{
		res = res.substr(0, res.length() - 2);
	}

	res += ")\n\\{\n";

	//then the body:
	char* cBody = _strdup((char*)body.c_str());
	char * token, *nextToken;

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

string Functions::PrintCall(VariablesVec vars)
{
	string res = name + "(";

	for (Variable i : vars.GetAllVariables())
	{
		res += i.id + ", ";
	}

	//remove the last comma and space from the for loop and return
	return res.substr(0, res.length() - 2) + ")";
}

string Functions::PrintCall()
{
	return name + "()";
}

VariablesVec Functions::GetParameters()
{
	return params;
}

vector<bool> Functions::GetRefs()
{
	return refs;
}
