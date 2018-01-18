#ifndef __FOR_LOOPS_H__
#define __FOR_LOOPS_H__

#include "Loops.h"


class ForLoops : public Loops
{
public:
	ForLoops(int minIters = 1, int maxIters = 5, bool improperLoops = false) : Loops(minIters, maxIters, improperLoops) {};

	ForLoops(Loops* old) : Loops(old) {};

	ForLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
		Loops(begin, symbol, end, incSymb, inc) {};

	~ForLoops() {};

	void Tests();

	string Print(string id, string body);

};

#endif
