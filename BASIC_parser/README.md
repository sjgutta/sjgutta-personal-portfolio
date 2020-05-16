# **Sajan Gutta - BASIC Parser - CSCI 104 Project**
This was a project written for my Data Structures class. The project is written in C++. It parses a simple programming language called BASIC by taking the text input, converting it into objects that represents each type of statement and its arguments, and then executing the statements in sequence. The program is pretty printed to the terminal and after that, its result is also printed. This project was a great example of the power of Object-Oriented Programming and a well-defined class structure. What may seem like an extremely difficult thing to do (using one programming language to parse and execute another) actually turned out to be quite possible and run in extremely small amounts of time with great accuracy. See the sections below to learn about the BASIC language, how my project was implemented, and how to run the program.

# The Language
## Variables
* integer variables: each variable stores a (signed) 32-bit integer. If a variable is read without having been initialized, its value is 0.
* one-dimensional arrays of integers: imagine the arrays to have "infinite" size, running from negative infinity to positive infinity. (For practical purposes, they have size equal to the range of a (signed) integer.) All (infinitely many) locations are 0 unless overwritten otherwise. Because the arrays are infinite, there can never be segfaults. If a user tries to read a location they have not written before, the value is 0.
## Expressions
When evaluating an expression, these are the rules to apply.

* a constant: that value is always its numerical value.
* an integer variable name <VAR>: the value is the value currently stored in that variable.
* an array evaluated at an integer position: the value is the array's value at the position, as described in the rules above.
* (<AEXPR1> + <AEXPR2>): the value is the sum of the values of <AEXPR1> and <AEXPR2>.
* (<AEXPR1> - <AEXPR2>): the value is the value of <AEXPR1> minus the value of <AEXPR2>.
* (<AEXPR1> * <AEXPR2>): the value is the value of <AEXPR1> multiplied with the value of <AEXPR2>.
* (<AEXPR1> / <AEXPR2>): the value is the value of <AEXPR1> divided by the value of <AEXPR2>, and rounded down to the nearest integer. (That is, the standard integer division.) If the value of <AEXPR2> is 0, then this is a division-by-0 error. The program will output an error message, including the line number where the error happened, the strings corresponding to <AEXPR1> and <AEXPR2>, and the values when the error happened. Then, the program will terminate. See below for exact format for error messages.
For all arithmetic expressions, the calculations should always result in integers that fit into a (signed) 32-bit integer to avoid overflows.

* <AEXPR1> = <AEXPR2>: evaluates to true if <AEXPR1> and <AEXPR2> evaluate to the same number.
* <AEXPR1> < <AEXPR2>: evaluates to true if <AEXPR1> evaluates to a (strictly) smaller number than <AEXPR2>.
* <AEXPR1> > <AEXPR2>: evaluates to true if <AEXPR1> evaluates to a (strictly) larger number than <AEXPR2>.

## Commands
Here is some detail on the commands in the language.

* PRINT <AEXPR>: prints the value of the arithmetic expression, evaluated according to the rules above. Always prints a newline after the value.
* LET <VAR> <AEXPR>: evaluates <AEXPR> and stores the resulting value into the variable <VAR>, overwriting the previous value if there was one.
* LET <VAR> [<AEXPR1>] <AEXPR2>: evaluates <AEXPR2> and stores the resulting value into the array <VAR>, at the position obtained from evaluating <AEXPR1>.
* GOTO <LINEJ>: Jump to the line <LINEJ>. Forgets which line it came from. Just resumes processing at the given line <LINEJ>. If there is no line numbered <LINEJ> in the program, it will print an error and terminate. See error messages below.
* IF <BEXPR> THEN <LINEJ>: evaluates <BEXPR> according to the rules given above. If it comes out true, then jumps to the line <LINEJ> (as in the case of GOTO). Otherwise just advances to the next line. As for GOTO, if the target line does not exist, it will output an error. (See error messages below.) If the condition comes out false (so there's no jump), and the target line does not exist, then no error is reported, as the program can safely continue running.
* GOSUB <LINEJ>: Jumps to the line <LINEJ>, and remembers where it came from. As for GOTO/IF, if the line <LINEJ> does not exist, then an error is printed (including the current line number and non-existing target line), and the program terminates. See below for details.
* RETURN: Go back to the line immediately after the line whence the most recent GOSUB jump started. See the more detailed example below. If there has been no applicable GOSUB jump, then an error message is printed; see below for the exact message and format.
* END: Terminate the execution of the program. Nothing can go wrong here.
  
## Error Messages
Whenever an error happens, the program prints an error message and terminates. Each error message begins with "Error in Line <LINE>: ", where <LINE> is the number of the line where the error occurred. After that, it prints an error-specific message, which will be one of the following:
* "Division by 0: <AEXP1> = <VAL1>, <AEXP2> = <VAL2>." Here, <AEXP1> and <AEXP2> are the pretty-printed text strings for the expressions, and <VAL1> and <VAL2> are the current value. (Presumably, when an error happened, <VAL2> has a value of 0.)
* "GOTO to non-existent line <LINEJ>." Here, <LINEJ> is the line that you were supposed to jump to, but which didn't exist.
* "IF jump to non-existent line <LINEJ>." Again, <LINEJ> is the line that you were supposed to jump to, but which didn't exist.
* "GOSUB to non-existent line <LINEJ>." Here, <LINEJ> is the line that you were supposed to jump to with GOSUB, but which didn't exist.
* "No matching GOSUB for RETURN."
* In all cases, after the error message is printed, the program terminates.

## Example Programs
Here are some simple examples of BASIC programs, and what they would output, so that you can familiarize yourself with the meanings of commands.

```text
5 LET HAN 42
10 LET SOLO -9
20 PRINT HAN
25 PRINT SOLO

```

You will need to be able to parse programs where line numbers are no longer consecutive. We only guarantee they will be positive, and in strictly increasing order (such as the above example), with execution starting at the lowest-numbered line. The above program would output:

```text
42
-9

```

```text
1 LET YODA 1
2 GOTO 4
3 LET YODA 2
4 PRINT YODA

```

This program would output  `1`, because by skipping line 3 (with the command  `GOTO 4`), we prevented YODA from being assigned the value 2.

```text
1 LET CHEWY 3
2 LET VADER 6
3 IF CHEWY < 4 THEN 5
4 PRINT CHEWY
5 PRINT VADER

```

This will print out only 6, since line 4 is skipped over.

```text
1 LET ANAKIN 1
2 GOSUB 6
3 PRINT ANAKIN
4 PRINT PADME
5 END
6 LET ANAKIN 2
7 LET PADME 3
8 RETURN

```

In the above program, ANAKIN will get set to 1, then the program will jump to line 6, overwriting ANAKIN with 2, setting PADME to 3, and then returning to the point it jumped from. It will then output ANAKIN, then PADME, then terminate. So the output will be

```text
2
3

```
## Exmaples of pretty-printed programs and syntax
Inside of the examples directory, you will see more examples of input programs and what the pretty printed version of them is supposed to look like, after all of the parsing is complete and the program has been represented by objects. You will also be able to see examples of how BASIC syntax should look.
### A detailed example of GOSUB and RETURN

To understand GOSUB and RETURN a bit better, consider the following piece of code:

```text
10 GOSUB 50
20 PRINT 20
30 RETURN
40 END
50 GOSUB 80
60 PRINT 60
70 RETURN
80 LET N 0
90 IF N > 1 THEN 130
100 PRINT N
110 LET N (N+1)
120 GOSUB 90
130 RETURN

```

Let's see what happens here.

1.  In line 10, the program jumps to line 50, remembering that it came from 10.
2.  From there, it jumps to 80, remembering that it came from 50.
3.  In 80, it initializes N to 0.
4.  Because N is not larger than 1, in line 90, it does not jump to 130, and instead prints N (which is 0) in line 100.
5.  It increments N in line 110, and then jumps to line 90, remembering that it came from line 120.
6.  Because N is still not greater than 1, it still does not jump, instead printing N (which is now 1) in line 100.
7.  It increments N to 2, and jumps from line 120 to line 90, remembering that it came from line 120.
8.  Now, in line 90, N  **is**  greater than 1, so it jumps to line 130.
9.  This is the first RETURN statement, and the most recent GOSUB was in step 7 of this description. It originated from line 120, so that's where the program returns (more precisely, to the next line, which is 130).
10.  That's another RETURN statement, and now, the most recent GOSUB that  **wasn't**  already accounted for is the one in step 5 of this description. It originated from line 120, so the program returns to line 130.
11.  That's  **yet**  another RETURN statement. At this point, the most recent unaccounted-for GOSUB is the one from step 2 of this description. It originated from line 50, so the RETURN statement jumps to the next line after 50, which is line 60.
12.  Here, it prints the number 60.
13.  Line 70 is a RETURN statement. Now, the next unaccounted-for GOSUB is the one from step 1, which originated from line 10. So the program next returns to line 20.
14.  Here, it prints the number 20.
15.  In line 30, we have another RETURN, but there are no more unmatched GOSUB statements left. At this point, an error occurs.

All in all, this would be the output:

```text
0
1
60
20
Error in Line 30: No matching GOSUB for RETURN.
```
# High-Level Approach to Implementation
1. A separate class was made for each type of arithmetic expression. Each one inherited from one base arithmetic expression class. They all have a print function that is over-ridden for the pretty printing functionality and a getValue function that is over-ridden for when the program is actual executed. 
2. The same approach was taken for the Boolean Expressions. These also took arithmetic expressions as data members. Both boolean expressions and arithmetic expressions are inside of the arithmetic.cpp and arithmetic.h files in the "interpreter" directory.
3. A separate class was made for each Command as well. Each command had a print function that was overriden as well as a used to execute that command. These can be found inside of the command.cpp and command.h files in the "intepreter" directory.
4. An overall interpreter class was created to actually parse the input file containing BASIC code. It would then create the appropriate command object and all of the proper expression objects within that command.
5. Finally, the interpreter class would loop through the list of commands that represented the program, executing the current command and acting accordingly until and END command was reached. You can find the code that does this part inside of the interpreter.h and interpreter.cpp files in the "interpreter" directory.

# Running the program
1. You can run the program in your terminal from this directory.
2. Typing make will compile the program.
3. You can run the program by using ./basic_intepreter and providing the input BASIC file as a command-line argument.
4. The output will be printed to the terminal.
