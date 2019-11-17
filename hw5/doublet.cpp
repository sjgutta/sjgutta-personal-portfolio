#include "heap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using namespace std;

string makeUpper(string input){
    string result = input;
    for(int i=0; i<int(input.length()); i++){
        if(result[i]>'A'){
            char temp = result[i];
            temp = char(int(temp) - 32);
            result[i] = temp;
        }
    }
    return result;
}

int calculate_heuristic(string input, string end){
    int result = 0;
    for(int i=0; i<int(input.length()); i++){
        if(input[i]!=end[i]){
            result++;
        }
    }
    return result;
}

int calculate_priority(string input, string end, int g_val){
    int h = calculate_heuristic(input, end);
    int f = g_val + h;
    int priority = f*(end.length()+1) + h;
    return priority;
}

int main(int argc, char* argv[]){
    if(argc<4){
        cout << "Not enough arguments" << endl;
        return 1;
    }
    string start = argv[1];
    start = makeUpper(start);
    string end = argv[2];
    end = makeUpper(end);
    if(start.length()!=end.length()){
        cout << "Start and end are not same length" << endl;
        return -1;
    }
    ifstream myfile(argv[3]);
    int numWords;
    myfile >> numWords;
    set<string> wordset;
    vector<string> valid_words;
    map<string, vector<string>> words_graph;
    map<string, bool> visited;
    for(int i=0; i<numWords; i++){
        string current;
        myfile >> current;
        current = makeUpper(current);
        if(current.length()==start.length()){
            wordset.insert(current);
            valid_words.push_back(current);
            visited[current] = false;
        }
    }
    for(int i=0; i<int(valid_words.size()); i++){
        string current = valid_words[i];
        for(int j=0; j<int(current.length()); j++){
            for(int k=0; k<26; k++){
                std::string temp = current;
                temp[j] = char(k+65);
                if(wordset.find(temp)!=wordset.end()){
                    words_graph[current].push_back(temp);
                }
            }
        }
    }
    //starting A* search part
    MinHeap<string> myheap(2);
    myheap.add(start, calculate_priority(start, end, 0));
}