// A general-purpose program for generating random questions
// based off of difficulty
// currently about arrays and loops (more to come)
//-----------------------------------------------------------------
// Made using "For Loop w Skew" as a template
//-----------------------------------------------------------------
// See 	README.md for question set difficulties and general notes
//-----------------------------------------------------------------

#include <iostream>
#include <ctime>
#include "../Question Categories/question.h"	//contains <fstream> and <string>
#include "../Question Categories/All Questions.h"
using namespace std;

int main(int argc, char *argv[])
{
	//File Control
	string mainCategory, subCategory, questionCategory; //Names of the categories
	string fileOut;										//Name of outputting file
	int numQuestions, baseDifficulty, rangeDifficulty, questionSet;

	//have an option to pass each argument on the command line
	//(the purpose of this is mostly for easy shell scripts)
	if (argc == 8)
	{
		mainCategory = argv[1];
		subCategory = argv[2];
		fileOut = argv[3];
		numQuestions = atoi(argv[4]);
		baseDifficulty = atoi(argv[5]);
		rangeDifficulty = atoi(argv[6]) + 1;
		questionSet = atoi(argv[7]);
	}
	else if (argc <= 2)
	{
		string fileControl, deadLine;	//Name of the file control

		if (argc == 1)
		{
			cout << "Enter control file name: " << endl;
			cin >> fileControl;
		}
		else //argc == 2
		{
			fileControl = argv[1];
		}

		//Opening the control file; FILE MUST BE IN SOLUTION DIRECTORY
		ifstream fileCtr(fileControl.c_str());

		if (!fileCtr.is_open())
		{
			cout << "Could not open the input file.\n";
			return 1;
		}

		//read in the arguments from the control file
		//(assuming it's in the standard format)
		getline(fileCtr, deadLine);
		getline(fileCtr, mainCategory);
		getline(fileCtr, deadLine);
		getline(fileCtr, subCategory);
		getline(fileCtr, deadLine);
		getline(fileCtr, fileOut);
		getline(fileCtr, deadLine);
		getline(fileCtr, deadLine);
		numQuestions = stoi(deadLine);
		getline(fileCtr, deadLine);
		getline(fileCtr, deadLine);
		baseDifficulty = stoi(deadLine);
		getline(fileCtr, deadLine);
		getline(fileCtr, deadLine);
		rangeDifficulty = stoi(deadLine) + 1;
		getline(fileCtr, deadLine);
		getline(fileCtr, deadLine);
		questionSet = stoi(deadLine);
		fileCtr.close();
	}
	else
	{
		cout << "Please use the correct amount of arguments.\n";
		return 1;
	}

	srand(unsigned int(time(NULL)));

	//Starting the output file
	ofstream file(fileOut.c_str());
	if (!file.is_open())
	{
		cout << "Error opening the output file.\n";
		return 1;
	}

	//dynamically create a new question based on desired question class
	Question* currQuestion;

	//Setting category the questions will be uploaded to.
	file << "$CATEGORY: $course$ / " + mainCategory + " / " + subCategory + to_string(baseDifficulty);
	file << "\n\n";

	//variable used to track when the difficulty changes so we can output the above for new difficulties
	int start = baseDifficulty;

	for (int i = 0; i < numQuestions; i++)
	{
		switch (questionSet)
		{
		case 0:
			currQuestion = new Arrays();
			questionCategory = "Arrays";
			break;
		case 1:
			currQuestion = new Loops(0);
			questionCategory = "For Loops";
			break;
		case 2:
			currQuestion = new Loops(2);
			questionCategory = "Do While Loops";
			break;
		case 3:
			currQuestion = new Loops(1);
			questionCategory = "While Loops";
			break;
		case 4:
			currQuestion = new Expressions();
			questionCategory = "Dynamic Expressions";
			break;
		case 5:
			currQuestion = new Functions();
			questionCategory = "Functions";
			break;
		case 6:
			currQuestion = new SwitchCases();
			questionCategory = "Switch Cases";
			break;
		case 7:
			currQuestion = new Identifiers();
			questionCategory = "Identifiers";
			break;
		case 8:
			currQuestion = new Conditionals();
			questionCategory = "Conditionals";
			break;
		default:
			cout << "Please select a proper question set.";
			return 1;
		}

		int difficulty = baseDifficulty + (rangeDifficulty * i / numQuestions);

		//this updates the category for every different difficulty
		if (difficulty != start)
		{
			file << "$CATEGORY: $course$ / " + mainCategory + " / " + subCategory + to_string(difficulty);
			file << "\n\n";
			start = difficulty;
		}

		currQuestion->SetDifficulty(difficulty);

		currQuestion->Generate();

		//Writing the question to the file.
		//Question
		file << "::" + questionCategory + " Level " << difficulty << " #" << setw(3) << setfill('0') << i << "::\n";
		currQuestion->Print(file);

		try
		{
			currQuestion->FinalAnswerCheck();
		}
		catch (SameAnswers a)
		{
			cout << "THE SAME ANSWERS HAVE APPEARED IN A QUESTION\n";
			cout << "Please fix your code.\n";

			delete currQuestion;
			currQuestion = NULL;
			return 2;
		}

		delete currQuestion;
		currQuestion = NULL;
	}

	file.close();

	return 0;
}
