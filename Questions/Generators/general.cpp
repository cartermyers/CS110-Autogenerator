//--------------------------------------------
//
// Implementation of the global functions
//
//--------------------------------------------

#include "general.h"

//searches the vector A up to lengthA and returns a value not in vector A
int FindUnique(const vector<int>& A, int lengthA, int range)
{
	//make sure we can actually find a unique value
	assert(range >= lengthA);

	int newVal = 0;
	bool unique = true;

	do
	{
		newVal = GenerateRand<int>(0, range);
		unique = true;

		for (int i = 0; i < lengthA; i++)
		{
			if (A[i] == newVal) //default 2 decimals of precision
			{
				unique = false;
				break;
			}
		}
	} while (!unique);

	return newVal;
}

float Operation(Symbols symb, float var1, DataTypes type1, float var2, DataTypes type2)
{
	//first, convert the values into their proper types
	//then, perform the operation
	//finally, convert the result to the most general datatype (in max)
	return Convert(max(type1, type2), Operation<float>(symb, Convert(type1, var1), Convert(type2, var2)));
}

string FloatToString(const float& val, bool isFixed, int precision)
{
	stringstream stream;

	if (isFixed)
	{
		stream << fixed;
	}

	stream << setprecision(precision) << val;
	return stream.str();
}