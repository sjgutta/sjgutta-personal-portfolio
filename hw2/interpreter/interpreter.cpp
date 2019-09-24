#include "interpreter.h"
#include <string>
#include <sstream>

//this constructs the interpreter and immediately parses program
Interpreter::Interpreter(std::istream& in) {
    this->parse(in);
}

//this destructor cleans up the commands which recursively delete
//underlying objects
Interpreter::~Interpreter() {
    for(int i=0; i<int(program.size());i++){
        delete program[i];
    }
}

//this is the function called to parse in stream
void Interpreter::parse(std::istream& in) {
    std::string line;
    while (getline(in, line)) {
        size_t line_number;
        std::stringstream stream(line);
        stream >> std::skipws >> line_number;

        std::string command;
        stream >> command;

        //constructing a print command with its output
        if(command == "PRINT"){
            NumericExpression* output = ParseNumeric(stream);
            Command* result = new PrintCommand(line_number, output);
            program.push_back(result);
        //constructing a let command
        }else if(command == "LET"){
            NumericExpression* variable = ParseVariableName(stream);
            NumericExpression* setValue = ParseNumeric(stream);
            Command* result = new LetCommand(line_number, setValue, variable);
            program.push_back(result);
        //constructing a goto command
        }else if(command == "GOTO"){
            int destination;
            stream >> destination;
            Command* result = new GoToCommand(line_number, destination);
            program.push_back(result);
        //constructing an if command
        }else if(command == "IF"){
            //creating boolean expression properly
            NumericExpression* left = ParseNumeric(stream);
            char booleanoperator = 0;
            stream >> booleanoperator;
            NumericExpression* right = ParseNumeric(stream);
            BooleanExpression* conditional = NULL;
            if(booleanoperator == '='){
                conditional = new EqualExpression(left, right);
            }else if(booleanoperator == '>'){ 
                //if operator is greater, flip arguments, make less expression
                conditional = new LessExpression(right, left);
            }else if(booleanoperator == '<'){
                conditional = new LessExpression(left, right);
            }
            //now getting rid of THEN from line of command
            std::string then;
            stream >> then;
            //now getting destination
            int destination;
            stream >> destination;
            //now building final command object and adding to program vector
            Command* result = new IfThenCommand(line_number, conditional, destination);
            program.push_back(result);
        //building gosub command
        }else if(command == "GOSUB"){
            int destination;
            stream >> destination;
            Command* result = new GoSubCommand(line_number, destination);
            program.push_back(result);
        //building return command
        }else if(command == "RETURN"){
            Command* result = new ReturnCommand(line_number);
            program.push_back(result);
        //building end command
        }else if(command == "END"){
            Command* result = new EndCommand(line_number);
            program.push_back(result);
        }
    }
}

//function to parse a numeric expression
NumericExpression* Interpreter::ParseNumeric(std::stringstream& stream){
    char first = 0;
    //get rid of whitespace before starting to parse
    stream >> std::ws;
    first = stream.peek();
    //if first char is a digit, parse a constant numeric
    if(first == '-' || isdigit(first)){
        int value;
        stream >> value;
        //use helper function to parse constant
        NumericExpression* result = ParseConstant(stream, value);
        return result;
    //if has parenthese, parse a binary expression
    //uses parse numeric recursively as a helper function
    }else if(first == '('){
        stream >> first;
        NumericExpression* left = ParseNumeric(stream);
        char binaryoperator = 0;
        stream >> binaryoperator;
        NumericExpression* right = ParseNumeric(stream);
        NumericExpression* result = NULL;
        //check for binary operator to make proper object
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
        //otherwise parse a variable name using helper
        NumericExpression* result = ParseVariableName(stream);
        return result;
    }
}

//parses a constant numeric expression and returns object
NumericExpression* Interpreter::ParseConstant(std::stringstream& stream, int value){
    NumericExpression* result = new Numeral(value);
    return result;
}

//function to parse a variable name and return object
NumericExpression* Interpreter::ParseVariableName(std::stringstream& stream){
    char next;
    std::string name = "";
    //getting rid of leading whitespace
    stream >> std::ws;
    //building up variable name until invalid character reached
    for(int i=0; i<8; i++){
        next = stream.peek();
        if(isupper(next)){
            stream >> next;
            std::string s(1, next);
            name  = name + s;
        }else{
            break;
        }
    }
    //getting rid of whitespace again
    stream >> std::ws;
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


//this function prints all the output to terminal
//loops through program vector and calls format for each command
void Interpreter::write(std::ostream& out) {
    for(int i=0; i<int(program.size()); i++){
        std::string write_out = program[i]->format();
        std::cout << write_out << std::endl;
    }
}
