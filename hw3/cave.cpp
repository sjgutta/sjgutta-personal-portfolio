//This file is used for cave exploration
//This solves Homework 3, part 5

#include <fstream>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int calculateDistance(ifstream& in){
    stack<char> s;
    int result = 0;
    char move;
    while(in >> move){
        char last_move = s.top();
        if(move==last_move){
            s.pop();
            result--;
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
    ifstream ifile;
    ifile.open(argv[1]);
    int result = calculateDistance(ifile);
    ifile.close();
    cout << result << endl;
    return 0;
}