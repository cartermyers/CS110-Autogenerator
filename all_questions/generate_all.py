#a script to run 'all_questions.exe' in './Release'
#to output every single category of questions in ''../../Examples'

#this is how we will execute commands
from subprocess import check_call

main_category = 'Examples'
#the order of subcategories is the same as the question set in control.txt
subcategories = ['Arrays', 'For_Loops_Printing', 'Do_While_Loops_Printing', \
                  'While_Loops_Printing', 'Expressions', 'Functions', \
                  'Switch_Cases', 'Identifiers', 'Conditionals']
num_questions = '1000'
base_difficulty = '1'
difficulty_range = '3'   #NOTE: this can only be 1 for Arrays and Functions

for i, subcategory in enumerate(subcategories):
    args = 'all_questions.exe'
    args += ' ' + main_category
    args += ' ' + subcategory
    #use a proper path for output files:
    args += ' ../../Examples/' + subcategory + '_examples.txt'
    args += ' ' + num_questions
    args += ' ' + base_difficulty

    #right now, we need special cases for Arrays and Functions
    if (subcategory != 'Arrays' and subcategory != 'Functions'):
        args += ' ' + difficulty_range
    else:
        args += ' 1'

    args += ' ' + str(i)    #this is the same as the question set

    check_call(args, shell=True, cwd='./Release')
