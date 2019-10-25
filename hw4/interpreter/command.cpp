#include "command.h"
#include <string>

using namespace std;

//command specific constructor to use in other contructors
Command::Command(int line){
    this->line_number = line;
}

//used to get the private line number value within subclasses
int Command::getLine() const{
    return line_number;
}

//print command functions defined
PrintCommand::PrintCommand(int line, NumericExpression* output) : 
    Command(line), output(output) {

}

PrintCommand::~PrintCommand() {
    delete this->output;
}

string PrintCommand::format() const {
    return to_string(this->getLine()) + " " + "PRINT" + " " + this->output->format();
}

void PrintCommand::execute(Interpreter* interpreter) const{
    cout << this->output->getValue() << endl;
}

//let command functions defined
LetCommand::LetCommand(int line, NumericExpression* setValue, 
    NumericExpression* variable) : Command(line), setValue(setValue), 
        variable(variable) {

}

LetCommand::~LetCommand() {
    delete this->setValue;
    delete this->variable;
}

string LetCommand::format() const {
    return to_string(this->getLine()) + " " + "LET" + " " + this->variable->format() + 
        " " + this->setValue->format();
}

void LetCommand::execute(Interpreter* interpreter) const{
    
}

//goto command functions defined
GoToCommand::GoToCommand(int line, int destination) 
    : Command(line), destination(destination){

}

GoToCommand::~GoToCommand() {
    
}

string GoToCommand::format() const {
    return to_string(this->getLine()) + " " + "GOTO" + 
        " <" + to_string(this->destination) + ">";
}

void GoToCommand::execute(Interpreter* interpreter) const{
    interpreter->goto_command(this->destination);
}

//If Then command functions defined
IfThenCommand::IfThenCommand(int line, BooleanExpression* conditional, int destination)
     : Command(line), conditional(conditional), destination(destination) {

}

IfThenCommand::~IfThenCommand() {
    delete this->conditional;
}

string IfThenCommand::format() const {
    return to_string(this->getLine()) + " " + "IF " + this->conditional->format() + 
        " THEN <" + to_string(this->destination) + ">";
}

void IfThenCommand::execute(Interpreter* interpreter) const{
    if(conditional->getValue()){
        interpreter->goto_command(this->destination);
    }else{
        interpreter->if_then_command();
    }
}

//GoSub command functions defined
GoSubCommand::GoSubCommand(int line, int destination) : Command(line), 
    destination(destination) {

}

GoSubCommand::~GoSubCommand() {
    
}

string GoSubCommand::format() const {
    return to_string(this->getLine()) + " " + "GOSUB" + " <" + 
        to_string(this->destination) + ">";
}

void GoSubCommand::execute(Interpreter* interpreter) const{
    interpreter->gosub_command(this->destination);
}

//return command functions defined
ReturnCommand::ReturnCommand(int line) : Command(line){

}

ReturnCommand::~ReturnCommand() {
    
}

string ReturnCommand::format() const {
    return to_string(this->getLine()) + " RETURN";
}

void ReturnCommand::execute(Interpreter* interpreter) const{
    interpreter->return_command();
}

//End command functions defined
EndCommand::EndCommand(int line) : Command(line){

}

EndCommand::~EndCommand() {
    
}

string EndCommand::format() const {
    return to_string(this->getLine()) + " END";
}

void EndCommand::execute(Interpreter* interpreter) const{
    interpreter->end_command();
}