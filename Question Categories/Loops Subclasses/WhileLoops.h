#ifndef __WHILE_LOOPS_H__
#define __WHILE_LOOPS_H__

#include "QLoops.h"

class LinearWhileLoops : public LinearLoops
{
public:
	LinearWhileLoops() : LinearLoops() {};

	LinearWhileLoops(QLoops* old) : LinearLoops(old) {};
	
	LinearWhileLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	LinearLoops(begin, symbol, end, incSymb, inc) {};

	~LinearWhileLoops() {};
	
	void Tests() {};

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

class ExpWhileLoops : public ExpLoops
{
public:
	ExpWhileLoops() : ExpLoops() {};

	ExpWhileLoops(QLoops* old) : ExpLoops(old) {};
	
	ExpWhileLoops(int begin, Symbols symbol, int end, Symbols incSymb, int inc) :
	ExpLoops(begin, symbol, end, incSymb, inc) {};
	
	~ExpWhileLoops() {};
	
	void Tests() {};

	string PrintLoop(QLoops* current, string id, string printerId);

	string PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId);
};

#endif
