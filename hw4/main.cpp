#include <iostream>
#include <fstream>
#include "interpreter/interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }

    ifstream input(argv[1]);
    Interpreter interpreter(input);
    interpreter.write(cout);
    cout << "NOW EXECUTING THE PROGRAM" << endl;
    cout << "-------------------------" << endl;
    interpreter.main_execute();
    return 0;
}
