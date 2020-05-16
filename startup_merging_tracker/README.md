# Sajan Gutta - Homework 3 - CSCI 104
This was another homework assignment written in my data structures class. It was written in C++ using a custom VM in Virtual Box that was made for the class. I used Visual Studio when writing most of my code.
## Startup Merging Tracker
* Startups merge so often, it's hard to keep track of who is in what company. Company A merges with Company B, and Company C merges with Company D, and then the two merged companies merge, and suddenly, employees from companies A and C find themselves being colleagues. This is getting sufficiently difficult to follow and so the assignment was to write a class that can be a startup merging tracker.
* Here is how it works. You have n students. Initially, each starts a startup company by himself/herself. Then, companies may merge. When there is a merge command, the program should be given the numbers of two representative students, one from each company. Then, for each of those two students, it finds the "biggest" company they are in, i.e., companies that are not subcompanies of any bigger company; let's call them A and B. Those two companies A and B are then merged into a new company; let's call it C. C will become the parent company of A and B.
* Sometimes, companies also split up again. When we call split, the program is again given a representative student. Then, it will find the biggest company that the student is in - let's call it A. As a result of the split, A should be completely removed, and the two companies that were at some point in the past merged to become A will now be individual companies without a parent again. (If the student is only in their own 1-person company, split does nothing.)
* For this assignment, a built a data structure that allows easy processing of a sequence of merges and splits, and answers queries about whether two students are in the same company.
* To illustrate this situation better, consider the following example with 5 students. After each command, you can see the structure of the nested companies with braces. The notation { {1}, { {2}, {3} } } means that we have a company with two subcompanies: the first subcompany is just student 1, while the second subcompany again has two subcompanies, one consisting of just student 2, the other consisting of just student 3.  
```text
merge (0,1)   => { {0}, {1} }, {2}, {3}, {4}
merge (2,3)   => { {0}, {1} }, { {2}, {3} }, {4}
merge (0,3)   => { { {0}, {1} }, { {2}, {3} } }, {4}
split (2)     => { {0}, {1} }, { {2},{3} }, {4}
split (2)     => { {0}, {1} }, {2}, {3}, {4}
merge (2,4)   => { {0}, {1} }, { {2}, {4} }, {3}
split (0)     => {0}, {1}, { {2}, {4} }, {3}

```
## Cave Program
* This program can be compiled using the command make cave.
* In this problem you are trying to explore a cave. In order to keep track of the way out, you carry a very long piece of string wrapped around a spool. When you take a step away from the direction you just came from, you let out a little more string. When you retrace a step and move back the way you came, you roll up a bit of string again. Your goal in this problem is to process a sequence of move and find out how much string is not rolled up.
* In a case such as N, S, E, and N being the sequence of steps, the output would be 2. This is because the first two steps offset each other. Then, the next two steps both unroll a unit of string.
* This problem was very simple to solve and mainly intended to focus on using the STL Stack.
## Combinations Program (Recursion)
* This was a very simple program written to take a string and output all of the permutations of its letters. For example, if  the input is USC then the output (in any order) would be USC, UCS, SUC, SCU, CUS, and CSU.
