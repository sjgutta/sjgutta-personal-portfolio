#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include "command.h"

//helping bypass circular dependencies
class Command;
class NumericExpression;

#include "arithmetic.h"

//This is the class for parsing the code, storing it
//also writes out the output using write function
class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void main_execute();
    void write(std::ostream& out);
    NumericExpression* ParseNumeric(std::stringstream& stream);
    NumericExpression* ParseConstant(std::stringstream& stream, int value);
    NumericExpression* ParseVariableName(std::stringstream& stream);
    void print_command(std::string name);
    void let_command(NumericExpression* variable);
    void goto_command(int destination);
    void then_command(int destination);
    void gosub_command(int destination);
    void return_command();
    void end_command(){this->is_over = true;}

    //some helper functions for this class
    int current_variable_value(std::string name);
    void populate_index_map();
    void increment_line();
    bool over_condition();
    bool variable_exists(std::string name);
private:
    void parse(std::istream& in);
    //this data member holds the lines of the program in a vector
    //each line is made into a command object
    std::vector<Command*> program;
    //track of current_line being executed
    int current_line;
    //tracking list of variable names that exist currently
    std::map<std::string, NumericExpression*> variables_list;
    //this maps line number in the program to index value in the vector
    std::map<int, int> index_reference_list;
    //boolean to track if program is over or not
    bool is_over;
    //stack to track last gosub command
    std::stack<int> gosubs_list;
};

#endif
