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

int AdditionExpression::getValue() const{
    return this->left->getValue() + this->right->getValue();
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

int SubtractionExpression::getValue() const{
    return this->left->getValue() - this->right->getValue();
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

int DivisionExpression::getValue() const{
    return this->left->getValue()/this->right->getValue();
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

int MultiplicationExpression::getValue() const{
    return this->left->getValue()*this->right->getValue();
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

//getname function for regular variable
string Variable::getName() const{
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
string ArrayVariable::getName() const{
    return this->name + "[" + to_string(this->index->getValue()) + "]";
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

string LessExpression::getLeftName() const{
    string name = this->left->getName();
    return name;
}

string LessExpression::getRightName() const{
    string name = this->right->getName();
    return name;
}

string EqualExpression::getLeftName() const{
    string name = this->left->getName();
    return name;
}

string EqualExpression::getRightName() const{
    string name = this->right->getName();
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

bool LessExpression::getValue() const{
    return this->left->getValue() < this->right->getValue();
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

bool EqualExpression::getValue() const{
    return this->left->getValue() == this->right->getValue();
}

bool EqualExpression::getValue(int first, int second) const{
    return first==second;
}

//helper functions to get left and right values for if-then commands
int LessExpression::getLeftValue() const{
    return this->left->getValue();
}

int LessExpression::getRightValue() const{
    return this->right->getValue();
}

int EqualExpression::getLeftValue() const{
    return this->left->getValue();
}

int EqualExpression::getRightValue() const{
    return this->right->getValue();
}