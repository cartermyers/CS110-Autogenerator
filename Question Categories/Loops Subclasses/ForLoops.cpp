#include "ForLoops.h"

//===============================================================================================
//========================================LinearForLoops Class===================================
//===============================================================================================

string LinearForLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return ForLoopsPrinters::PrintLoop(current, id, printerId);
}

string LinearForLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return ForLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}

//===============================================================================================
//========================================ExpForLoops Class======================================
//===============================================================================================

string ExpForLoops::PrintLoop(QLoops* current, string id, string printerId)
{
	return ForLoopsPrinters::PrintLoop(current, id, printerId);
}

string ExpForLoops::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	return ForLoopsPrinters::PrintLoop(outer, outerId, inner, innerId, printerId);
}