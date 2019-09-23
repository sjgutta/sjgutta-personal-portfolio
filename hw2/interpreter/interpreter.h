#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include "command.h"
#include "arithmetic.h"

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);
    NumericExpression* ParseNumeric(std::stringstream& stream);
    NumericExpression* ParseConstant(std::stringstream& stream);
    NumericExpression* ParseVariableName(std::stringstream& stream);
private:
    void parse(std::istream& in);
    std::vector<Command*> program;
};

#endif
