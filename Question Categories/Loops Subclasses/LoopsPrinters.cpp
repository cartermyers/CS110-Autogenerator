//Simple functions that print out loops in the proper format

#include "QLoops.h"

//For Loops
string ForLoopsPrinters::PrintLoop(QLoops* current, string id, string printerId)
{
	//first the for loop declaration
	string res = "for (int " + id + " = " + to_string(current->GetStart()) + "; " + id + " " + SYMBOLS[current->GetSymb()] + " "
		+ to_string(current->GetStop()) + "; " + id + " = " + id + " " + SYMBOLS[current->GetIncSymb()] + " " + to_string(current->GetIncrement()) + ")\n";

	//then the printing	statement
	res += "\\{\n\tcout << " + printerId + " << \" \";\n\\}";

	return res;
}

string ForLoopsPrinters::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	//start off with the first for loop
	string res = "for (int " + outerId + " = " + to_string(outer->GetStart()) + "; " + outerId + " " + SYMBOLS[outer->GetSymb()] + " "
		+ to_string(outer->GetStop()) + "; " + outerId + " = " + outerId + " " + SYMBOLS[outer->GetIncSymb()] + " " + to_string(outer->GetIncrement()) + ")\n";

	//then the next loop:
	res += "\\{\n\tfor (int " + innerId + " = " + to_string(inner->GetStart()) + "; " + innerId + " " + SYMBOLS[inner->GetSymb()] + " "
		+ to_string(inner->GetStop()) + "; " + innerId + " = " + innerId + " " + SYMBOLS[inner->GetIncSymb()] + " " + to_string(inner->GetIncrement()) + ")\n";

	//then the print statement:
	res += "\t\\{\n\t\tcout << " + printerId + " << \" \";\n\t\\}\n\\}";

	return res;
}

//While Loops
string WhileLoopsPrinters::PrintLoop(QLoops* current, string id, string printerId)
{
	string res = "int " + id + " = " + to_string(current->GetStart()) + ";\n";

	res += "while (" + id + " " + SYMBOLS[current->GetSymb()] + " " + to_string(current->GetStop()) + ")\n";
	res += "\\{\n\tcout << " + printerId + " << \" \";\n";
	res += "\t" + id + " " + SYMBOLS[(current->GetIncSymb())] + "= " + to_string(current->GetIncrement()) + ";\n\\}";

	return res;
}

string WhileLoopsPrinters::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	string res = "int " + outerId + " = " + to_string(outer->GetStart()) + ";\n";
	res += "while (" + outerId + " " + SYMBOLS[outer->GetSymb()] + " " + to_string(outer->GetStop()) + ")\n";
	res += "\\{\n\tint " + innerId + " = " + to_string(inner->GetStart()) + ";\n";
	res += "\twhile (" + innerId + " " + SYMBOLS[inner->GetSymb()] + " " + to_string(inner->GetStop()) + ")\n";
	res += "\t\\{\n\t\tcout << " + printerId + " << endl;\n";
	res += "\t\t" + innerId + " " + SYMBOLS[(inner->GetIncSymb())] + "= " + to_string(inner->GetIncrement()) + ";\n\t\\}\n";
	res += "\\}";

	return res;
}

//do while loops

string DoLoopsPrinters::PrintLoop(QLoops* current, string id, string printerId)
{
	string res = "int " + id + " = " + to_string(current->GetStart()) + ";\n";
	res += "do\n\\{\n";
	res += "\tcout << " + printerId + " << \" \";\n";
	res += "\t" + id + " = " + id + " " + SYMBOLS[current->GetIncSymb()] + " " + to_string(current->GetIncrement()) + ";\n";
	res += "\\} while (" + id + " " + SYMBOLS[current->GetSymb()] + " " + to_string(current->GetStop()) + ");\n";

	return res;
}

string DoLoopsPrinters::PrintLoop(QLoops* outer, string outerId, QLoops* inner, string innerId, string printerId)
{
	//first variable declaration
	string res = "int " + outerId + " = " + to_string(outer->GetStart()) + ";\n";
	res += "do\n\\{\n";
	//second variable declaration
	res += "\tint " + innerId + " = " + to_string(inner->GetStart()) + ";\n";
	res += "\tdo\n\t\\{";
	//print statement
	res += "\t\tcout << " + printerId + " << \" \";\n";
	//second variable update
	res += "\t\t" + innerId + " = " + innerId + " " + SYMBOLS[inner->GetIncSymb()] + " " + to_string(inner->GetIncrement()) + ";\n";
	//second loop condtion
	res += "\t\\} while (" + innerId + " " + SYMBOLS[inner->GetSymb()] + " " + to_string(inner->GetStop()) + ");\n";
	//first variable update
	res += "\t" + outerId + " = " + outerId + " " + SYMBOLS[outer->GetIncSymb()] + " " + to_string(outer->GetIncrement()) + ";\n";
	//first loop condition
	res += "\\} while (" + outerId + " " + SYMBOLS[outer->GetSymb()] + " " + to_string(outer->GetStop()) + ");\n";

	return res;
}