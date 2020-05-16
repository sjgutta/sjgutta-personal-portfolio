# Sajan Gutta - HW1 - README
The code in this directory was written for a homework assignment in my data structures class. It is all written in C++. A VM specific to the course and on Virtual Box was used for the assignments. I wrote my code primarily in Visual Studio.
* This assignment focused mainly on memory management, file I/O, and exception handling in C++.
## Code compiles with g++ -g -Wall -std=c++11 tracker.cpp -o tracker
* This is assuming you are in same directory as tracker.cpp
## For the file-reverser the same command above works
* Just use g++ -g -Wall -std=c++11 file_reverser.cpp -o reverser
* This will run with any file as a second argument and output correctly to the terminal
* This is assuming the file is properly formatted
# Functionalities
## File Reverser
* This program takes the name of a file on the command line as an argument.
* It reads in the file and prints out the file reversed to the terminal.
## Experiment Tracker
### Commands
* START n: starts a new set of experiments, with n subjects involved. These n subjects (numbered 0 to n - 1) are added to experiment 0. We will call this "experiment 0", but it's really just the subject pool; see below.
* ADD: adds a new experiment, giving it the next higher number. If there are 3 experiments going, they are numbered 1-3 (remember that 0 is the subject pool), so ADD would add experiment 4 next.
* MOVE x y n m: moves the subjects numbered n to m (inclusive) from experiment x to experiment y. What this means is that the subjects with these numbers are removed from experiment x, and all higher-numbered subjects have their numbers shifted down, so they now start being numbered at x. In other words, subjects' numbering is always kept consecutive. When they are added to experiment y, they are added at the next highest numbers. So if one adds 5 more subjects to an experiment having 7 subjects already, they are numbered 7 to 11, since the previous 7 were numbered 0 to 6. It is perfectly fine to move subjects from an experiment to the same experiment. Notice that when doing so, the internal numbering of the subjects in the experiment will likely change. Also, the experiment will be listed multiple times (as often as the subject was in it).
* QUERY x n: returns the sequence of experiments that the current nth subject in experiment x was exposed to, in order. If the subject was part of experiments 0 (subject pool), 1, 6, and is currently number 5 in experiment 2, then QUERY 2 5 would output 1 6 2. The subject pool is not outputted, even if the subject is later returned to it.
### Overall
* The assignment was to write this program to help a scientists who plans to subject different sets of subjects to different experiments. The scientist needs to keep track of which subjects are in which experiment, and which experiments they have been subjected to in the past, so that when the experiment succeeds, they can remember what experiments were performed to get it.
* The program maintains a 2-d array of strings subject_history[][], where subject_history[i] stores all of the subjects currently involved in experiment i, and subject_history[i][j] contains a string listing all of the experiments that this particular subject has been a part of.
* The program takes two strings as input: the first specifies an input file, and the second specifies an output file. The input file can contain many different slates of experiments. Any time the program encounters the line START n for some parameter n, the previous experiment is completely discarded, and a new slate of experiments is started from scratch. Once the last line in the input file has been processed, the program correctly deallocates all memory and terminates.
* The results of the commands are written to the ouput file. A number of errors relating to invalid arguments and logic in the input are accounted for, and will be outputted to the ouput file along with the line number they occurred on.
