#include "arithmetic.h"
#include <string>

using namespace std;

//numeric expression specific constructor to use in other contructors
NumericExpression::NumericExpression(int value){
    this->value = value;
}

//used to get the private value within subclasses
int NumericExpression::getValue() const{
    return value;
}

//addition expression functions defined
AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

//subtraction expression functions defined
SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

SubtractionExpression::~SubtractionExpression() {
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}


//division expression functions defined
DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

DivisionExpression::~DivisionExpression() {
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}


//multiplication expression functions defined
MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

MultiplicationExpression::~MultiplicationExpression() {
    delete this->left;
    delete this->right;
}

string MultiplicationExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}


//constructor functions for numeral, variable, and array variables
Numeral::Numeral(int value): NumericExpression(value){
    this->value = value;
}

Variable::Variable(int value, string name): NumericExpression(value){
    this->value = value;
    this->name = name;
}

ArrayVariable::ArrayVariable(int value, NumericExpression* index, string name): NumericExpression(value), index(index){
    this->value = value;
    this->name = name;
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
BooleanExpression::BooleanExpression(bool value){
    this->value = value;
}

bool BooleanExpression::getValue() const{
    return value;
}

//less than boolean subclass functions
LessExpression::LessExpression(NumericExpression* left, NumericExpression* right) : BooleanExpression(left->getValue() < right->getValue()), left(left), right(right){

}

LessExpression::~LessExpression() {
    delete this->left;
    delete this->right;
}

string LessExpression::format() const {
    return "[" + this->left->format() + " < " + this->right->format() + "]";
}

//equal expression subclass functions
EqualExpression::EqualExpression(NumericExpression* left, NumericExpression* right) : BooleanExpression(left->getValue() == right->getValue()), left(left), right(right){

}

EqualExpression::~EqualExpression() {
    delete this->left;
    delete this->right;
}

string EqualExpression::format() const {
    return "[" + this->left->format() + " < " + this->right->format() + "]";
}