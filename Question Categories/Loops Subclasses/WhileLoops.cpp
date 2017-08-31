#include "WhileLoops.h"

//===============================================================================================
//===========================================LinearWhileLoops Class=================================
//===============================================================================================

string LinearWhileLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return WhileLoopsPrinters::PrintLoop(current, id, printerId);
}

string LinearWhileLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return WhileLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}

//===============================================================================================
//===========================================ExpWhileLoops Class==============================
//===============================================================================================

string ExpWhileLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return WhileLoopsPrinters::PrintLoop(current, id, printerId);
}

string ExpWhileLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return WhileLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}