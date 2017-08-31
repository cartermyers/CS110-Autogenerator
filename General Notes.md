# General Notes
-------------------------------------------------------------------

#### Documentation Beginnning March 30, 2017
##### (Most recent at top):

##### 01/08/17
I think I am almost done with the current iteration of these questions. I've
added more categories from older questions (ones completed before I started on this project)
from the shared Dropbox, including While Loops, Do While Loops, Identifiers, and Conditionals.
I've noted all the current types of questions at the beginning of this file. I've also added
different question types for Loops, such as increments using '\*' and '/' as well as printing
out the incremented variable for a tougher type of question. I've also managed to generalize
each category of Loops (For Loops, While Loops, and Do While Loops) to each have the same type
of question, and have the ability to easily change the question types by modifying some parameters
in the functions (For more info, see TypeOne(), TypeTwo(), etc. in Loops.cpp).
I am continuing to add more tests to each class, but I have spent my own time checking them and
feel confident that they all work. I will still add more tests for added benefit. Other than that,
I cannot think of more to refactor or to change. I will simply look for more questions to add
in the future or better modifications of the ones currently here.

-CM


##### 04/07/17
Some quick updates: The return type function question has been completed.
I'm not completely settled on all of the design choices, but it works as expected
and tests are being written. I've also made another common data structure called
Parameters, which uses Variables as a base, and simply adds a vector to keep track
if the parameters are reference. I'm also thinking about adding a vector in Parameters
for operators, because as it stands, every single Functions question uses an expression.

I've added some more Loops questions to include \*= and /= operators. I've only
use 2 and 10 as the increment because those are easy numbers to calculate. With these
additions, I've replaced some of the old Loops questions (which I found a little boring
or redundant) to stay with 4 'difficulties'.

As for the greater design, I've written documentation in a given format for each function
found in the .h files. Because of this, I've split up each class into it's own .h file,
in case there's  ever a situation where some programs would only want one type of question.
As a result, each Question subclass must use its own members and can't use any other classes'
members for the sake of modularity, or something.

I've also been contemplating the structure of classes themselves. For example, I thought
it would be a good idea to have each random element as private data members and then randomize
them in the constructor. If needed, each individual 'difficulty' could change the members
themselves however they wanted (see Loops or SwitchCases). However, I run into a bit of a
problem when I have classes that use fundamentally different questions, such as Arrays or
Functions. One solution to this would be to keep the practice of having every random element
as a private member that is initialized in the constructor - this means that each different
question (such as in Arrays or Functions) would need to be a class on its own, probably a subclass
or a composition of the category's class. Another solution would be to make the data member thing
optional and only use it where it makes good sense. For now, I've just decided to keep it optional.
As long as the class functions are well documented, it's clear where each of the data members
are or are not used.
There are some standards however, such as CheckUniqueAnswers() and Tests(), which should be
implemented and stable across every class. I should make a list of these standards and add them at
the top of this document.

I also plan to integrate some of the older questions from the dropbox, so they can be part of this
main program.

-CM

##### 11/06/17
Even though it's been a while since this had been updated, I've been working
quite a bit on the questions. I've taken out the old Functions question, and added a
(what I believe to be) better, simpler, and more directed question based on reference
parameters. I plan to add one on function returns and data types soon. I've also added
some Switch Case questions based around simple switch case statements.
More importantly, I've decided to refactor a lot of the structure of the code for
reusability and readability. I made a Variables struct to mimic variables contained within
a certain scope. I've added commonly used functions to the Question class (some with templates,
although I'm not completely sure about the necessity of some templates). I've implemented
more robust tests and checks for the program, and I've decided to have a general, basic
flow for questions (i.e. a function to generate the answer, to print the question, etc.) so
it is easier to test and follow and resuse (although I haven't kept up with the documentation
that well). Even though these are mostly ideas, I feel like I have a better direction and
understanding of what this program needs to be very easy code to use. There is a lot of work
still to be done (which I hope to accomplish by the end of the summer), but progress is being
made.

-CM

##### 03/05/17
After a long break from working on these questions, I changed the implementation
of the arrays so it starts out with a unique set of elements (i.e. no repeating elements),
and if a new element needs to be added for the wrong arrays (due to having the same answer),
it will add a completely new element that is not in any of the other arrays. This is not a
very clever solution, but it rarely happens, so it is mostly a safety measure.

##### 15/04/17
After the first quiz run through in late March with a few minor mishaps,
I've decided to consider some general tenets or rules:

a) Always make sure the right answer is available and unique. This seems simple enough,
but it is cruicial. To follow up, always make sure each wrong answer is unique, even
if a wrong answer may seem somewhat nonsensical. While the first attempt at generating
wrong answers can try to be clever or eloquent, it is worthless if two wrong answers are
the same. So generally, have a surefire, simple backup in the case that two answers are the same.

b) Don't have too much randomness. In the first implementation of the functions questions,
there were simple too many cases for an individual question which resulted in (i) hard to test answers and wrong
answers, but more importantly (ii) questions without purpose. Some functions returned
a / a, which isn't a very meaningful question. Even though the random element lies at
the essence of these questions, a question with every single element random can have
questions that seem pointless. In general, Questions should have a general motive or
topic at the outset (such as pass-by-reference variables). This makes them easier to implement,
to test, and to maintain.

-CM
