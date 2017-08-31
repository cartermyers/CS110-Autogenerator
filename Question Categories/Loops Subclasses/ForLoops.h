#ifndef __FOR_LOOPS_H__
#define __FOR_LOOPS_H__

#include "QLoops.h"

class ExpForLoops : public ExpLoops
{
public:
	~ExpForLoops() {};

	ExpForLoops() : ExpLoops() {};

	ExpForLoops(QLoops* old) : ExpLoops(old) {};
	
	ExpForLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	ExpLoops(begin, symbol, end, incSymb, inc) {};

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

class LinearForLoops : public LinearLoops
{
public:
	LinearForLoops() : LinearLoops() {};

	LinearForLoops(QLoops* old) : LinearLoops(old) {};
	
	LinearForLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	LinearLoops(begin, symbol, end, incSymb, inc) {};
	
	~LinearForLoops() {};

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

#endif
