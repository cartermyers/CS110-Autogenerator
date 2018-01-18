

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "Variables.h"

struct Parameter : public Variable
{
	Parameter(string newID, DataTypes newType, float newVal, bool newRef) : Variable(newID, newType, newVal), ref(newRef) { };

	bool ref;
};

#endif