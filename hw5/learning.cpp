//Sajan Gutta
//solving problem 2 on hw5

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//defining the recursive function that gets the answer
void bestClassCombo(string* class_names, float* workloads, float* learning, int num_classes,
    float &max_learning, float work_capacity, int checking_class, float worked, float learned){
    //checking if too much work is now included
    if(worked>=work_capacity){
        return;
    }
    //checking if no classes left to include
    if(checking_class>=num_classes){
        return;
    }
    //checking if max_learning should be increased
    if(learned>max_learning){
        max_learning = learned;
    }
    //making recursive calls, one including next class and one not
    bestClassCombo(class_names, workloads, learning, num_classes, max_learning, work_capacity,
        checking_class + 1, worked + workloads[checking_class], learned + learning[checking_class]);
    bestClassCombo(class_names, workloads, learning, num_classes, max_learning, work_capacity,
        checking_class + 1, worked, learned);

}

int main(int argc, char *argv[]){
    if(argc<2){
        cout << "Please provide an input file" << endl;
        return 1;
    }
    ifstream file;
    file.open(argv[1]);
    int num_classes;
    float work_capacity;
    file >> num_classes >> work_capacity;
    //reading in classes into an array
    string* class_names = new string[num_classes];
    float* workloads = new float[num_classes];
    float* learning = new float[num_classes];
    for(int i=0; i<num_classes; i++){
        string current_class;
        float current_work, current_learning;
        file >> current_class >> current_work >> current_learning;
        class_names[i] = current_class;
        workloads[i] = current_work;
        learning[i] = current_learning;
    }
    //integer for the max learning
    ///to be passed by reference
    float max_learning = 0;
    //modify max_learning with backtracing and print the result
    //making the call to the recursive function that solves the problem
    bestClassCombo(class_names, workloads, learning, num_classes, max_learning, work_capacity,
        0, 0, 0);
    cout << max_learning << endl;
    //cleaning up memory and closing file
    delete [] class_names;
    delete [] workloads;
    delete [] learning;
    file.close();
    return 0;
}