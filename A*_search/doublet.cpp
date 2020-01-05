#include "heap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using namespace std;

//helper function to keep everything in capital letters
string makeUpper(string input){
    string result = input;
    for(int i=0; i<int(input.length()); i++){
        if(result[i]>'Z'){
            char temp = result[i];
            temp = char(int(temp) - 32);
            result[i] = temp;
        }
    }
    return result;
}

//helper function to calculate h value for a string
int calculate_heuristic(string input, string end){
    int result = 0;
    for(int i=0; i<int(input.length()); i++){
        if(input[i]!=end[i]){
            result++;
        }
    }
    return result;
}

//helper function to calculate priority taking data about a node
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
    //if the words aren't equal length, immediately end program
    if(start.length()!=end.length()){
        cout << "No transformation" << endl;
        cout << 0 << endl;
        return 0;
    }
    ifstream myfile(argv[3]);
    int numWords;
    myfile >> numWords;
    //set of words we were given to check if a word exists later
    set<string> wordset;
    //set of valid words to loop through when building graph
    vector<string> valid_words;
    //map to store adjacency list for the actual graph
    //maps a string to a vector that holds it's adjacent list of edges
    map<string, vector<string>> words_graph;
    //map to hold whether a string is visited or not during search
    map<string, bool> visited;
    //map to track distance travelled during search, useful for num of transformations
    map<string, int> distance;
    //reading in words and storing data properly
    for(int i=0; i<numWords; i++){
        string current;
        myfile >> current;
        current = makeUpper(current);
        //make sure word is valid by comparing it's length to the start
        if(current.length()==start.length()){
            wordset.insert(current);
            valid_words.push_back(current);
            visited[current] = false;
            distance[current] = 0;
        }
    }
    //start building graph
    for(int i=0; i<int(valid_words.size()); i++){
        string current = valid_words[i];
        //for each valid word, go through words that are one character different
        //use the set to see if those words exist in the dictionary
        //if they do exist, build an edge in the graph
        for(int j=0; j<int(current.length()); j++){
            for(int k=0; k<26; k++){
                std::string temp = current;
                temp[j] = (char)(k+65);

                if(temp==current){
                    continue;
                }

                if(wordset.find(temp)!=wordset.end()){
                    words_graph[current].push_back(temp);
                }
            }
        }
    }
    //starting A* search part
    //track the order that a word is added for when priority must be updated
    map<string, int> order_added;
    //track number of adds and number of expansions
    int added_count = 0;
    int expansion_count = 0;
    //create heap, add start, and initiliaze added information properly
    MinHeap<string> myheap(2);
    myheap.add(start, calculate_priority(start, end, 0));
    order_added[start] = added_count;
    added_count++;
    while(!myheap.isEmpty()){
        string visiting = myheap.peek();
        myheap.remove();
        //can print visiting here to see expansions
        //see if we are visiting the final string, which means search is complete
        if(visiting == end){
            cout << distance[end] << endl;
            cout << expansion_count << endl;
            return 0;
        }
        expansion_count++;
        //loop through neighboring nodes
        for(int i=0; i<int(words_graph[visiting].size()); i++){
            string checking = words_graph[visiting][i];
            //if the neighboring node is not visited or is closer to start via this path
            //then we enter the loop
            if(!visited[checking] || distance[visiting] + 1 < distance[checking]){
                //modify the distance
                distance[checking] = distance[visiting] + 1;
                //if node is not visited yet, add to heap w/ proper priority
                if(!visited[checking]){
                    myheap.add(checking, calculate_priority(checking, end, distance[checking]));
                    //mark node as visited
                    visited[checking] = true;
                    //account for the node being added now
                    order_added[checking] = added_count;
                    added_count++;
                }else{
                    //if already visited, update the priority for the node instead
                    myheap.update(order_added[checking], calculate_priority(checking, end, distance[checking]));
                }
            }
        }
    }
    //if we reach here, the search was complete and the end string was never visited
    //this means that no transformation should be outputted
    cout << "No transformation" << endl;
    cout << expansion_count << endl;
    return 0;
}