//This program can reverse a file and output the result to the terminal
//Sajan Gutta
//Monday, September 2, 2018

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[]){
    //get file name to open and open it
    string file = argv[1];
    ifstream ifile(file.c_str());
    //get length of characters and trash extra newline character
    int length;
    ifile >> length;
    string trash_line;
    getline(ifile, trash_line);
    //Now dynamically allocate array and build it
    //the array contains the file backwards
    char* backwards_file = new char [length];  
    for(int i=length; i>0; i--){
        char temp;
        ifile >> std::noskipws >> temp;
        backwards_file[i-1] = temp;
    }
    //Turning character array into a c++ string
    string result(backwards_file);
    cout << result << endl;
    //cleaning up memory, closing file, and returning 0
    ifile.close();
    delete [] backwards_file;
    return 0;
}