// A program to perform tests on each question category
// NOTE: All tests should be written in the function Tests() for each class
// as it can test private functions that are not callable in this scope.
// This program is mainly an environment to run the Tests() functions

#include <iostream>
#include <cassert>
#include "../Question Categories/question.h"
#include "../Question Categories/All Questions.h"


int main()
{
  Question* tester = new Arrays();

  //first, test the superclass:
  tester->Question::Tests();

  //then all the subclasses:

  //Arrays:
  tester->Tests();
  delete tester;

  //for loops
  tester = new Loops(0);
  tester->Tests();
  delete tester;

  //do while loops
  tester = new Loops(2);
  tester->Tests();
  delete tester;

  //while loops
  tester = new Loops(1);
  tester->Tests();
  delete tester;

  //expressions
  tester = new Expressions();
  tester->Tests();
  delete tester;

  //functions
  tester = new Functions();
  tester->Tests();
  delete tester;

  //switch cases
  tester = new SwitchCases();
  tester->Tests();
  delete tester;

  //identifiers
  tester = new Identifiers();
  tester->Tests();
  delete tester;

  //conditionals
  tester = new Conditionals();
  tester->Tests();
  delete tester;

  tester = NULL;

  return 0;
}
