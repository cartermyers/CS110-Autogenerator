//--------------------------------------------
//
// Implementation of the Variables class
//
//--------------------------------------------

#include "Variables.h"

VariablesVec::VariablesVec()
{
	
}

/*
TODO: change this to a random initializer
VariablesVec::VariablesVec(int length) : size(length)
{
	for (int i = 0; i < length; i++)
	{
		order.push_back(i);
		//allocate other vectors with 0s or null:
		//this may be changed later
		//INVESTIGATE IF THIS CONSTRUCTOR IS ACTUALLY USEFUL IN ASSIGNING MEANINGFUL VALUES
		dataTypes.push_back(Int);
		ids.push_back("");
		vals.push_back(0);
	}
}
*/

VariablesVec::VariablesVec(vector<Variable> oldVars)
{
	for (Variable i : oldVars)
	{
		AddVariable(i);
	}
}

void VariablesVec::Randomize()
{
	random_shuffle(vars.begin(), vars.end());
}

void VariablesVec::AddVariable(Variable newVar, bool uniqueId, bool properType)
{
	assert(newVar.type < Void);

	if (uniqueId)
	{
		assert(IdNotInVars(newVar.id));
	}
	
	if (properType)
	{
		newVar.val = Convert(newVar.type, newVar.val);
	}

	vars.push_back(newVar);
}

Variable VariablesVec::GetVariable(string id)
{
	for (Variable i : vars)
	{
		if (i.id == id)
		{
			return i;
		}
	}

	//no variable found with that id, throw error:
	throw runtime_error("No variable found with that id.");
}

Variable VariablesVec::GetVariable(int index)
{
	return vars[index];
}

void VariablesVec::SetVariableVal(string id, float newVal, bool forceType)
{
	for (size_t i = 0; i < vars.size(); i++)
	{
		if (vars[i].id == id)
		{
			if (forceType)
			{
				vars[i].val = Convert(vars[i].type, newVal);
			}
			else
			{
				vars[i].val = newVal;
			}
			break;
		}
	}
}

void VariablesVec::SetVariableVal(int index, float newVal, bool forceType)
{
	if (forceType)
	{
		vars[index].val = Convert(vars[index].type, newVal);
	}
	else
	{
		vars[index].val = newVal;
	}
}

void VariablesVec::RemoveVariable(string id)
{
	for (int i = 0; i < vars.size(); i++)
	{
		if (id == GetVariable(i).id)
		{
			vars.erase(vars.begin() + i);
			break;
		}
	}
}

string VariablesVec::Print(bool noLiterals)
{
	string res = "";

	for (Variable i : vars)
	{
		//print the number if it is not a number (or if it is a number, print it if noLiterals is false)
		if (!noLiterals || !isdigit(i.id[0]))
		{
			res += DATA_TYPES[i.type] + " " + i.id + " = " + FloatToString(i.val) + ";\n";
		}
	}

	return res;
}

vector<Variable> VariablesVec::GetAllVariables()
{
	return vars;
}

size_t VariablesVec::Size()
{
	return vars.size();
}

void VariablesVec::Copy(VariablesVec old, bool uniqueId, bool properType)
{
	for (Variable i : old.GetAllVariables())
	{
		AddVariable(i, uniqueId, properType);
	}
}

bool VariablesVec::IdNotInVars(string id)
{
	for (Variable i : vars)
	{
		if (i.id == id)
		{
			return false;
		}
	}

	//id is not in variables so
	return true;
}


