#include "arithmetic.h"
#include <string>
#include <exception>

using namespace std;

//numeric expression specific constructor to use in other contructors
NumericExpression::NumericExpression(int value){
    this->value = value;
}

//used to get the private value within subclasses
int NumericExpression::getValue(Interpreter* interpreter) const{
    return value;
}

void NumericExpression::setValue(int new_value){
    this->value = new_value;
}

//addition expression functions defined
AdditionExpression::AdditionExpression(NumericExpression* left, 
    NumericExpression* right) : left(left), right(right) {

}

AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

int AdditionExpression::getValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter) + this->right->getValue(interpreter);
}

//subtraction expression functions defined
SubtractionExpression::SubtractionExpression(NumericExpression* left, 
    NumericExpression* right) : left(left), right(right) {

}

SubtractionExpression::~SubtractionExpression() {
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}

int SubtractionExpression::getValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter) - this->right->getValue(interpreter);
}

//division expression functions defined
DivisionExpression::DivisionExpression(NumericExpression* left, 
    NumericExpression* right) : left(left), right(right) {

}

DivisionExpression::~DivisionExpression() {
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}

int DivisionExpression::getValue(Interpreter* interpreter) const{
    int right_value = this->right->getValue(interpreter);
    int left_value = this->left->getValue(interpreter);
    if(right_value==0){
        throw invalid_argument("Division by 0: " + this->left->format() + "=" +
            std::to_string(left_value) + ", " +  this->right->format() + "=" + std::to_string(right_value));
    }
    return this->left->getValue(interpreter)/this->right->getValue(interpreter);
}

//multiplication expression functions defined
MultiplicationExpression::MultiplicationExpression(NumericExpression* left, 
    NumericExpression* right) : left(left), right(right) {

}

MultiplicationExpression::~MultiplicationExpression() {
    delete this->left;
    delete this->right;
}

string MultiplicationExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}

int MultiplicationExpression::getValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter)*this->right->getValue(interpreter);
}

//constructor functions for numeral, variable, and array variables
Numeral::Numeral(int value): NumericExpression(value){
    this->value = value;
}

Variable::Variable(int value, string name): NumericExpression(value){
    this->value = value;
    this->name = name;
}

Variable::Variable(string name): name(name){
    
}

int Variable::getValue(Interpreter* interpreter) const{
    return interpreter->current_variable_value(this->getName(interpreter));
}

//getname function for regular variable
string Variable::getName(Interpreter*) const{
    return this->name;
}

ArrayVariable::ArrayVariable(NumericExpression* index, string name): index(index), name(name){
    
}

ArrayVariable::ArrayVariable(int value, NumericExpression* index, string name): 
    NumericExpression(value), index(index){
    this->value = value;
    this->name = name;
}

//getname function for array variable
//helps track existing variables during execution
string ArrayVariable::getName(Interpreter* interpreter) const{
    return this->name + "[" + to_string(this->index->getValue(interpreter)) + "]";
}

int ArrayVariable::getValue(Interpreter* interpreter) const{
    return interpreter->current_variable_value(this->getName(interpreter));
}

//string format functions for numeral, variable, and array variables
string Numeral::format() const{
    return to_string(this->getValue());
}

string Variable::format() const{
    return this->name;
}

string ArrayVariable::format() const{
    return this->name + "[" + this->index->format() + "]";
}

//destructor functions for numeral, variable, and array variables
Numeral::~Numeral() {
    
}

Variable::~Variable() {
    
}

ArrayVariable::~ArrayVariable() {
    
}

//defining boolean base class
BooleanExpression::BooleanExpression(){
    
}

string LessExpression::getLeftName(Interpreter* interpreter) const{
    string name = this->left->getName(interpreter);
    return name;
}

string LessExpression::getRightName(Interpreter* interpreter) const{
    string name = this->right->getName(interpreter);
    return name;
}

string EqualExpression::getLeftName(Interpreter* interpreter) const{
    string name = this->left->getName(interpreter);
    return name;
}

string EqualExpression::getRightName(Interpreter* interpreter) const{
    string name = this->right->getName(interpreter);
    return name;
}


//less than boolean subclass functions
LessExpression::LessExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

LessExpression::~LessExpression() {
    delete this->left;
    delete this->right;
}

string LessExpression::format() const {
    return "[" + this->left->format() + " < " + this->right->format() + "]";
}

bool LessExpression::getValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter) < this->right->getValue(interpreter);
}

bool LessExpression::getValue(int first, int second) const{
    return first< second;
}

//equal expression subclass functions
EqualExpression::EqualExpression(NumericExpression* left, NumericExpression* right){
    this->left = left;
    this->right = right;
}

EqualExpression::~EqualExpression() {
    delete this->left;
    delete this->right;
}

string EqualExpression::format() const {
    return "[" + this->left->format() + " = " + this->right->format() + "]";
}

bool EqualExpression::getValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter) == this->right->getValue(interpreter);
}

bool EqualExpression::getValue(int first, int second) const{
    return first==second;
}

//helper functions to get left and right values for if-then commands
int LessExpression::getLeftValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter);
}

int LessExpression::getRightValue(Interpreter* interpreter) const{
    return this->right->getValue(interpreter);
}

int EqualExpression::getLeftValue(Interpreter* interpreter) const{
    return this->left->getValue(interpreter);
}

int EqualExpression::getRightValue(Interpreter* interpreter) const{
    return this->right->getValue(interpreter);
}