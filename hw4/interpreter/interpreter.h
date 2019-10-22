#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include "command.h"
#include "arithmetic.h"

//This is the class for parsing the code, storing it
//also writes out the output using write function
class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);
    NumericExpression* ParseNumeric(std::stringstream& stream);
    NumericExpression* ParseConstant(std::stringstream& stream, int value);
    NumericExpression* ParseVariableName(std::stringstream& stream);
private:
    void parse(std::istream& in);
    //this data member holds the lines of the program in a vector
    //each line is made into a command object
    std::vector<Command*> program;
};

#endif
