PA2 - coolness

I first started out declaring the formula 


coolness.c  : The user can run your program with zero, one, or two command line arguments. In the event that arguments are passed, T will always be the first argument, and V always the second. If only one argument is passed, it is T. You will need to check that any passed arguments are within the acceptable values: -99 <= T <= 50 and 0.5 <= V. If either of the arguments are unacceptable, exit with code 1 and print the following error message. Thus we calculaute using the formula to calculate the windspeed.

Formula : 35.74 + (0.6215 * T) - (35.75 * pow(V, 0.16)) + (0.4275 * T * pow(V, 0.16));

Makefile: This is a shortcut of compiling our c file, where we can make clean to get rid of executables and add our math library

testing.sh : this is where I make testcases in order to check if its pass or fail

testing.out : these are the results/otuput that directed from testing.sh

How to run program? :
in the command line we do : ./coolness
want to an input? : ./coolness [temperature]
want two inputs? : ./coolness [temperature] [wind speed]

Building:
in the command line type "make" to compile the code
then "make clean" after you are done 

-Josh Chow
-Student ID: 1971403
