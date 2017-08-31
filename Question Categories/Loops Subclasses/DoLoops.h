#ifndef __DO_LOOPS_H__
#define __DO_LOOPS_H__

#include "QLoops.h"

class LinearDoLoops : public LinearLoops
{
public:
	LinearDoLoops() : LinearLoops() {};

	LinearDoLoops(QLoops* old) : LinearLoops(old) {};
	
	LinearDoLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	LinearLoops(begin, symbol, end, incSymb, inc) {};

	~LinearDoLoops() {};

	void Tests();

	//overload the compute loop fuction
	int ComputeLoop(int min, int max);

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);

private:
	//need a different show iterations too:
	vector<int> ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb);
};

class ExpDoLoops : public ExpLoops
{
public:
	ExpDoLoops() : ExpLoops() {};

	ExpDoLoops(QLoops* old) : ExpLoops(old) {};
	
	ExpDoLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	ExpLoops(begin, symbol, end, incSymb, inc) {};

	~ExpDoLoops() {};

	void Tests();

	int ComputeLoop(int min, int max);

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);

private:
	//need a different show iterations too (same as LinearDoLoops)
	vector<int> ShowIterations(int begin, Symbols symbol, int end, int inc, Symbols incSymb);
};

#endif
