//This file is used for cave exploration
//This solves Homework 3, part 5

#include <fstream>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int calculateDistance(ifstream& in){
    //building a stack
    stack<char> s;
    int result = 0;
    //getting the move in a character
    char move;
    while(in >> move){
        char last_move = '\0';
        if(!s.empty()){
            last_move = s.top();
        }
        //check if opposite moves, there are 4 cases
        if(move=='N' && last_move == 'S'){
            s.pop();
            result--;
        }else if(move=='S' && last_move == 'N'){
            s.pop();
            result--;
        }else if(move=='E' && last_move == 'W'){
            s.pop();
            result--;
        }else if(move=='W' && last_move == 'E'){
            s.pop();
            result--;
        //if not opposite moves, increase length 
        //and push latest move
        }else{
            s.push(move);
            result++;
        }
        //get rid of extra newline character
        string trash;
        getline(in,trash);
    }
    return result;
}

int main(int argc, char* argv[]){
    if(argc<2){
        cout << "No input file detected." << endl;
        return 1;
    }
    //open instream for file
    ifstream ifile;
    ifile.open(argv[1]);
    //calculate the result and return it
    int result = calculateDistance(ifile);
    //close file, print result
    ifile.close();
    cout << result << endl;
    return 0;
}