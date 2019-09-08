#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

class TheRani {
public:
    TheRani(char* input_path, char* output_path);
    ~TheRani();
    // Call execute and handles exceptions
    void main();

private:
    int experiment_count;       // You will need to track the number of experiments
    int* subject_counts;        // For each, the number of subjects
    string** subject_history;   // And for each subject, their history
    int subject_total;

    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    // Called in the main method
    void execute(const string& line);

    // Possible helper: deallocate all current members
    void destroy_current();
};

TheRani::TheRani(char* input_path, char* output_path) : experiment_count(0), input(input_path), output(output_path) {
    

}

TheRani::~TheRani() {

}

//deallocates all dynamically allocated arrays
void TheRani::destroy_current(){
    if subject_history != NULL{
        for(int i=0;i<experiment_count;i++){
            delete [] subject_history[i];
        }
        delete [] subject_history
    }
    if subject_counts != NULL{
        delete [] subject_counts;
    }
}
// Possible helper: read an integer argument from a stream
void readInt(stringsteam stream){
    int temp;
    stream >> temp;
    return temp;
}


void TheRani::main() {
    string line;
    while (getline(input, line)) {
        try {
            this->execute(line);
        } catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output << "Error on line ?: " << e.what() << endl;
        }
    }
}

void TheRani::execute(const string& line) {
    string command;
    stringstream stream(line);  // Initialize the stream with the line
    stream >> command;          // Read the first word, which is the command

    if (command == "START") {   // This code should be edited for error checking
        int subject_pool_count;
        stream >> subject_pool_count;
        if (subject_pool_count < 0) {
            throw out_of_range("argument out of range");
        }
        subject_total = subject_pool_count;
        // Your code here
        if subject_history{
            destroy_current();
        }
        subject_history = new string*[experiment_count+1];
        subject_history[0] = new string[subject_pool_count];
        subject_counts = new int[experiment_count+1];
        subject_counts[0] = subject_pool_count;
    } else if (command == "ADD"){
        //incrementing the number of experiments
        experiment_count++;
        //creating temporary new arrays for the revised experiment set
        string** temp_subject_history = new string*[experiment_count+1];
        for(int i=0; i<experiment_count+1; i++){
            temp_subject_history[i] = new string[subject_total];
        }
        int* temp_subject_counts = new int[experiment_count+1];
        //copying over old experiment set info.
        //loop through old subject history and into the temp one
        for(int i=0; i<experiment_count; i++){
            for(int j=0; j<subject_counts[i];j++){
                temp_subject_history[i][j] = subject_history[i][j];
            }
        }
        for(int i=0; i<experiment_count;i++){
            temp_subject_counts[i] = subject_counts[i];
        }
        //setting new experiment subject count to 0
        temp_subject_counts[experiment_count-1] = 0;
        //deleting old experiment set with helper function
        destroy_current();
        //setting data members equal to new experiment set
        subject_history = temp_subject_history;
        subject_counts = temp_subject_counts;
    } else if (command == "MOVE"){
        //getting arguments into variables
        int experiment1 = readInt(stream);
        int experiment2 = readInt(stream);
        int sublow = readInt(stream);
        int subhigh = readInt(stream);

    } else if (command == "QUERY"){
        
    }else{
        
    }// else if (more conditions) { ...
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }

    TheRani tr(argv[1], argv[2]);
    tr.main();
    return 0;
}
