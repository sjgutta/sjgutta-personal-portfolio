#include "interpreter.h"
#include <string>
#include <sstream>

Interpreter::Interpreter(std::istream& in) {
    this->parse(in);
}

Interpreter::~Interpreter() {
    for(int i=0; i<int(program.size());i++){
        delete program[i];
    }
}

void Interpreter::parse(std::istream& in) {
    std::string line;
    while (getline(in, line)) {
        size_t line_number;
        std::stringstream stream(line);
        stream >> std::skipws >> line_number;

        std::string command;
        stream >> command;

        if(command == "PRINT"){
            NumericExpression* output = ParseNumeric(stream);
            Command* result = new PrintCommand(line_number, output);
            program.push_back(result);
        }else if(command == "LET"){

        }else if(command == "GOTO"){
            
        }else if(command == "IF"){
            
        }else if(command == "GOSUB"){
            
        }else if(command == "RETURN"){
            
        }else if(command == "END"){
            
        }
    }
}

NumericExpression* Interpreter::ParseNumeric(std::stringstream& stream){
    char first = 0;
    stream >> first;
    if(first == '-' || isdigit(first)){
        int value = first - '0';
        NumericExpression* result = ParseConstant(stream, value);
        return result;
    }else if(first == '('){
        NumericExpression* left = ParseNumeric(stream);
        char binaryoperator = 0;
        stream >> binaryoperator;
        NumericExpression* right = ParseNumeric(stream);
        NumericExpression* result = NULL;
        if(binaryoperator=='+'){
            result = new AdditionExpression(left, right);
        }else if(binaryoperator=='-'){
            result = new SubtractionExpression(left, right);
        }else if(binaryoperator=='*'){
            result = new MultiplicationExpression(left, right);
        }else{
            result = new DivisionExpression(left, right);
        }
        //have to get rid of close parentheses
        char trash;
        stream >> trash;
        //now return the resulting expression that was parsed
        return result;
    }else{
        NumericExpression* result = ParseVariableName(stream);
        return result;
    }
}

NumericExpression* Interpreter::ParseConstant(std::stringstream& stream, int value){
    NumericExpression* result = new Numeral(value);
    return result;
}

NumericExpression* Interpreter::ParseVariableName(std::stringstream& stream){
    char next;
    std::string name;
    //building up variable name until invalid character reached
    for(int i=0; i<8; i++){
        next = stream.peek();
        if(isupper(next)){
            stream >> next;
            name += std::to_string(next);
        }else{
            break;
        }
    }
    //checking if variable is an array variable
    next = stream.peek();
    if(next=='['){
        stream >> next;
        NumericExpression* index = ParseNumeric(stream);
        //getting rid of close bracket
        stream >> next;
        //constructing array variable
        NumericExpression* result = new ArrayVariable(index, name);
        return result;
    }else{ //if not array variable, construct variable
        NumericExpression* result = new Variable(name);
        return result;
    }
}



void Interpreter::write(std::ostream& out) {
    for(int i=0; i<int(program.size()); i++){
        std::string write_out = program[i]->format();
        std::cout << write_out << std::endl;
    }
}
