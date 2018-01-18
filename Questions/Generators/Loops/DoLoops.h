#ifndef __DO_LOOPS_H__
#define __DO_LOOPS_H__

#include "Loops.h"

class DoLoops : public Loops
{
public:
	DoLoops(int minIters = 1, int maxIters = 5, bool improperLoops = false) : Loops(minIters, maxIters, improperLoops) {};

	DoLoops(Loops* old) : Loops(old) {};
	
	DoLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
		Loops(begin, symbol, end, incSymb, inc) {};

	~DoLoops() {};

	void Tests();

	//overload the compute loop fuction
	int ComputeLoop();

	string Print(string id, string body);

private:
	//need a different show iterations too:
	vector<int> ShowIterations();
};


#endif
