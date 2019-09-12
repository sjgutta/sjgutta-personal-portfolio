#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <string>
#include <math.h>

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
    bool started; //data member to track if experiment started


    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    // Called in the main method
    void execute(const string& line);

    // Possible helper: deallocate all current members
    void destroy_current();
        
    //helper function to read stream to int
    int readInt(stringstream& ss);
};

TheRani::TheRani(char* input_path, char* output_path) : experiment_count(0), 
input(input_path), output(output_path) {
    subject_counts = NULL;
    subject_history = NULL;
    subject_total=0;
    started = false;
}

TheRani::~TheRani() {
    destroy_current();
}

//deallocates all dynamically allocated arrays
void TheRani::destroy_current(){
    if (subject_history != NULL){
        for(int i=0;i<experiment_count+1;i++){
            delete [] subject_history[i];
        }
        delete [] subject_history;
    }
    if (subject_counts != NULL){
        delete [] subject_counts;
    }
}
// Possible helper: read an integer argument from a stream
int TheRani::readInt(stringstream& ss){
    double temp;
    //checking if enough arguments were given based on if stream is empty
    if(ss.rdbuf()->in_avail() == 1){
        throw invalid_argument("too few arguments");
    }
    ss >> temp;
    //checking if an invalid argument type was given
    //first checking if string based on ss failing
    if(ss.fail()){
        throw invalid_argument("expected integer argument");
    }
    double intpart;
    //then checking if a double was given or 
    //an actual integer based on the decimal part
    if(modf(temp, &intpart)!=0){
        throw invalid_argument("expected integer argument");
    }
    int result = int(temp);
    return result;
}


void TheRani::main() {
    string line;
    int line_number = 1;
    while (getline(input, line)) {
        try {
            this->execute(line);
            line_number+=1;
        }catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output << "Error on line " << line_number << 
            ": " << e.what() << endl;
            return;
        }
    }
}

void TheRani::execute(const string& line) {
    string command;
    stringstream stream(line);
    stream >> command;      
    if (!started&&command!="START"){
        throw runtime_error("no subjects yet");
    } else if (command == "START") { 
        int subject_pool_count;
        subject_pool_count = readInt(stream);
        if (subject_pool_count < 0) {
            throw out_of_range("argument out of range");
        }
        subject_total = subject_pool_count;
        experiment_count=0;
        // Your code here
        if(subject_history){
            destroy_current();
        }
        subject_history = new string*[1];
        subject_history[0] = new string[subject_pool_count];
        subject_counts = new int[experiment_count+1];
        subject_counts[0] = subject_pool_count;
        //setting started indicator to true
        started =  true;
    } else if (command == "ADD"){
        //creating temporary new arrays for the revised experiment set
        string** temp_subject_history = new string*[experiment_count+2];
        for(int i=0; i<experiment_count+2; i++){
            temp_subject_history[i] = new string[subject_total];
        }
        int* temp_subject_counts = new int[experiment_count+2];
        //copying over old experiment set info.
        //loop through old subject history and into the temp one
        for(int i=0; i<experiment_count+1; i++){
            for(int j=0; j<subject_counts[i];j++){
                temp_subject_history[i][j] = subject_history[i][j];
            }
        }
        for(int i=0; i<experiment_count+1;i++){
            temp_subject_counts[i] = subject_counts[i];
        }
        //setting new experiment subject count to 0
        temp_subject_counts[experiment_count+1] = 0;
        //deleting old experiment set with helper function
        destroy_current();
        //setting data members equal to new experiment set
        subject_history = temp_subject_history;
        subject_counts = temp_subject_counts;
        //incrementing the number of experiments
        experiment_count++;
    } else if (command == "MOVE"){
        //getting arguments into variables
        int experiment1 = readInt(stream);
        int experiment2 = readInt(stream);
        int sublow = readInt(stream);
        int subhigh = readInt(stream);
        stringstream convert;
        convert << experiment2;
        string experiment2_string = convert.str();
        //checking if any arguments are negative
        if(experiment1<0||experiment2<0){
            throw invalid_argument("argument out of range");
        }
        if(sublow<0||subhigh<0){
            throw invalid_argument("argument out of range");
        }
        //checking if any arguments are nonexistent experiments
        if(experiment1>experiment_count||experiment2>experiment_count){
            throw invalid_argument("argument out of range");
        }
        //checking if any number in range arguments 
        //is within number of subjects for the experiment
        if(sublow>=subject_counts[experiment1]||
            subhigh>=subject_counts[experiment1]){
            throw invalid_argument("argument out of range");
        }
        //checking if reasonable range of subjects to move was given
        if(sublow>subhigh){
            throw logic_error("invalid range of subjects to move");
        }
        //figuring out subjects moved and lowering subject_counts
        int moved = subhigh - sublow + 1;
        subject_counts[experiment1] -= moved;
        //setting string of subject's new location
        for(int i=sublow; i<=subhigh; i++){
            subject_history[experiment2][subject_counts[experiment2]] = 
            subject_history[experiment1][i] + " " + experiment2_string;
            subject_counts[experiment2]++;
        }
        //now moving subjects over in experiment that lost subjects
        for(int i=sublow; i<subject_counts[experiment1];i++){
            subject_history[experiment1][i] = 
                subject_history[experiment1][i+moved];
        }
    } else if (command == "QUERY"){
        //getting arguments in variables and extracting history
        int experiment = readInt(stream);
        int nth = readInt(stream);
        //checking if any arguments were negative
        if(experiment<0||nth<0){
            throw invalid_argument("argument out of range");
        }
        //checking if experiment exists
        if(experiment>experiment_count){
            throw invalid_argument("argument out of range");
        }
        //checking if the subject exists
        if(nth>=subject_counts[experiment]){
            throw invalid_argument("argument out of range");
        }
        string history = subject_history[experiment][nth];
        //filtering and outputting the history
        stringstream ss(history);
        int temp;
        while(ss>>temp){
            if(temp!=0){
                output << temp << " ";
            }
        }
        output << endl;
    }else{
        throw runtime_error("command does not exist");
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
