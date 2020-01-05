/*This program is written for Homework #3, part 4
The program takes in a string and prints out
all possible permutations of the string*/

#include <string>
#include <iostream>

void permutationsHelper(std::string in, std::string curr){
    //print out the individual combo if in is empty
    if(int(in.length())==0){
        std::cout << curr << std::endl;
        return;
    }
    //call all different possible combos using for loop
    //one call per character in string in
    for(int i=0; i<int(in.length()); i++){
        std::string temp = in.substr(0,i)+in.substr(i+1,in.length()-1);
        permutationsHelper(temp, curr+in[i]);
    }
}

void permutations(std::string in){
    if(int(in.length())>0){
        //calling helper function
        permutationsHelper(in,"");
    }
}