#a script to run 'all_questions.exe' in './Release'
#to output every single category of questions in ''../../Examples'

#this is how we will execute commands
from subprocess import check_call

main_category = 'Examples'
#the order of subcategories is the same as the question set in control.txt
subcategories = ['Arrays', 'For_Loops_Coutning', 'Do_While_Loops_Coutning', \
                  'While_Loops_Coutning', 'For_Loops_Printing', 'Do_While_Loops_Printing', \
                  'While_Loops_Printing', 'Expressions', 'Functions', \
                  'Switch_Cases', 'Identifiers', 'Conditionals']
num_questions = '1000'
base_difficulty = '1'
difficulty_range = '4'   #NOTE: this can only be 3 for Arrays, Loops_Printing and Functions

for i, subcategory in enumerate(subcategories):
    args = 'all_questions.exe'
    args += ' ' + main_category
    args += ' ' + subcategory
    #use a proper path for output files:
    args += ' ../../Examples/' + subcategory + '_examples.txt'
    args += ' ' + num_questions
    args += ' ' + base_difficulty

    #right now, we need special cases for Arrays
    if (subcategory == 'Arrays' or ('Loops_Printing' in subcategory) or subcategory == 'Functions'):
        args += ' 3'
    else:
        args += ' ' + difficulty_range

    args += ' ' + str(i)    #this is the same as the question set

    #print subcategory + " " + args

    check_call(args, shell=True, cwd='./Release')
