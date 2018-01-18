#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "general.h"
#include "Parameters.h"

class Functions
{
public:
	//differentDataTypes means it generates data types that are different than the given types in vars, unless the variable is a reference
	Functions(DataTypes returnDataType, string functionName, VariablesVec* vars = NULL, vector<bool> refParams = {}, bool differentDataTypes = false, DataTypes minType = Int, DataTypes maxType = Int);

	void PassVariables(VariablesVec vars, bool convertType = true);

	string PrintDefinition(string body);

	string PrintCall(VariablesVec vars);

	string PrintCall();

	VariablesVec GetParameters();

	vector<bool> GetRefs();

private:
	DataTypes returnType;
	string name;

	//parameters of the function:
	VariablesVec params;
	vector<bool> refs;		//NOTE: refs.size() == params.size
};

#endif // !__FUNCTIONS_H__
