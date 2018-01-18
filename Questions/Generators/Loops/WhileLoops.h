#ifndef __WHILE_LOOPS_H__
#define __WHILE_LOOPS_H__

#include "Loops.h"

class WhileLoops : public Loops
{
public:
	WhileLoops(int minIters = 1, int maxIters = 5, bool improperLoops = false) : Loops(minIters, maxIters, improperLoops) {};

	WhileLoops(Loops* old) : Loops(old) {};

	WhileLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
		Loops(begin, symbol, end, incSymb, inc) {};

	~WhileLoops() {};

	void Tests();

	string Print(string id, string body);
};

#endif
