// ------------------------------------------
// Variables.h
// Definition of the Variables class
// This is a simple data structure that can be quite useful.
// It is meant to represent all variables in a given scope.
// All vectors are in parallel, but sometimes its nice to
// randomly reorder them simultaneously. This is what the order vector is for
//--------------------------------------------

#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include "general.h"

struct Variable
{
	Variable() : id("-1"), type((DataTypes)-1), val(-1) { };

	Variable(string newID, DataTypes newType, float newVal) : id(newID), type(newType), val(newVal) { };

	string id;
	DataTypes type;
	float val;
};


//CONSIDER CREATING A TEMPLATE CLASS FOR THIS
class VariablesVec {
public:

	VariablesVec();
	/*==================== Variables() ====================
	DESC:	A basic constructor
	PARAM:	No parameters
	PRE: 	No preconditions
	POST: 	size is set to 0
	LOC: 	question.cpp
	EX:
	=====================================================*/

	//TODO: change this to a random generator
	//VariablesVec(int length);
	/*==================== Variables(int length) ====================
	DESC:	A basic constructor based on the desired length
	PARAM:	int length - the number of variables in Variables
	PRE: 	No preconditions
	POST: 	All data members are superficially initialized, with size = length
	LOC: 	question.cpp
	EX:
	=====================================================*/

	VariablesVec(vector<Variable> oldVars);

	//a deep copy
	void Copy(VariablesVec old, bool uniqueId = true, bool properType = true);

	void Randomize();

	void AddVariable(Variable newVarb, bool uniqueId = true, bool properType = true);

	//remove a variable based on its id
	void RemoveVariable(string id);

	vector<Variable> GetAllVariables();

	//return the value of a variable given the name
	Variable GetVariable(string id);

	Variable GetVariable(int index);

	void SetVariableVal(string id, float newVal, bool forceType = true);

	void SetVariableVal(int index, float newVal, bool forceType = true);

	string Print(bool noLiterals = true);
	//if the variable's id starts with a number, it is not printed.

	size_t Size();

	//maybe overload (or alter) AddVariable to include a random generator

protected:

	//check if the id already exists in this "scope"
	bool IdNotInVars(string id);

private:
	vector<Variable> vars;
};

#endif