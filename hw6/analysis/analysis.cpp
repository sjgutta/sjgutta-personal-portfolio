#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include "../avl/avlbst.h"
#include "../splay/splay.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc<3){
        cout << "Not enough arguments provided" << endl;
        return -1;
    }
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    //initializing the trees
    AVLTree<string, int> myAVL;
    SplayTree<string, int> mySplay;

    vector<string> wordList;
    string current;
    while(inFile >> current){
        wordList.push_back(current);
    }

    int insertions = wordList.size()*2;

    clock_t start;
    double duration;

    start = clock();

    int numRepititions = 100;

    for(int i=0; i<numRepititions; i++){
        myAVL.clear();
        for(int i=0; i<int(wordList.size()); i++){
            pair<string, int> inserting(wordList[i], 0);
            myAVL.insert(inserting);
        }
    }

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    double final_avl_time = duration/numRepititions;

    start = clock();
    
    for(int i=0; i<numRepititions; i++){
        mySplay.clear();
        for(int i=0; i<int(wordList.size()); i++){
            pair<string, int> inserting(wordList[i], 0);
            mySplay.insert(inserting);
        }
    }

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    double final_splay_time = duration/numRepititions;

    outFile << insertions << " insertions" << endl;
    outFile << "AVL: " << final_avl_time << " seconds" << endl;
    outFile << "Splay: " << final_splay_time << " seconds" << endl;
    outFile << "Splay expensive: " << mySplay.report();

    return 0;
}