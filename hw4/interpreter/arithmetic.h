#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <vector>

class NumericExpression;
class BooleanExpression;
class Interpreter;
#include "interpreter.h"

//base class
class NumericExpression {
public:
    NumericExpression(){}
    NumericExpression(int value);
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;
    void setValue(int new_value);
    virtual std::string getName(Interpreter*) const{return "";}
    virtual int getValue() const{return value;}
    virtual int getValue(Interpreter*) const;
protected:
    int value;
};

//Class for numeric expressions with just a number value
class Numeral : public NumericExpression {
public:
    Numeral(int value);
    ~Numeral();
    virtual std::string format() const;
};

//class for variable with a name
class Variable : public NumericExpression {
public:
    Variable(std::string name);
    Variable(int value, std::string name);
    ~Variable();
    virtual std::string format() const;
    virtual std::string getName(Interpreter*) const;
    virtual int getValue(Interpreter*) const;
private:
    std::string name;
};

//class for variable with a name and index
class ArrayVariable : public NumericExpression {
public:
    ArrayVariable(NumericExpression* index, std::string name);
    ArrayVariable(int value, NumericExpression* index, std::string name);
    ~ArrayVariable();
    virtual std::string format() const;
    virtual std::string getName(Interpreter*) const;
    virtual int getValue(Interpreter*) const;
private:
    NumericExpression* index;
    std::string name;
};


//class for an addition numeric expression
class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();
    virtual int getValue(Interpreter*) const;
    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

//class for a subtraction numeric expression
class SubtractionExpression : public NumericExpression {
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();
    virtual int getValue(Interpreter*) const;
    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


//class for a division expression
class DivisionExpression : public NumericExpression {
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();
    virtual int getValue(Interpreter*) const;
    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


//class for a multiplication expression
class MultiplicationExpression : public NumericExpression {
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();
    virtual int getValue(Interpreter*) const;
    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


//Now working on making boolean expressions work
class BooleanExpression {
public:
    BooleanExpression();
    virtual ~BooleanExpression() {}
    virtual std::string format() const = 0;
    virtual bool getValue(Interpreter*) const = 0;
    virtual bool getValue(int,int) const = 0;
    //functions for handling variables as arguments in a boolean expression
    virtual std::string getLeftName(Interpreter*) const = 0;
    virtual std::string getRightName(Interpreter*) const = 0;
    //getting left and right values
    virtual int getLeftValue(Interpreter*) const = 0;
    virtual int getRightValue(Interpreter*) const = 0;
};

//less than boolean expression
class LessExpression : public BooleanExpression {
public:
    LessExpression(NumericExpression* left, NumericExpression* right);
    ~LessExpression();
    virtual bool getValue(Interpreter*) const;
    virtual bool getValue(int,int) const;
    virtual std::string format() const;
    virtual std::string getLeftName(Interpreter*) const;
    virtual std::string getRightName(Interpreter*) const;
    //getting left and right values
    virtual int getLeftValue(Interpreter*) const;
    virtual int getRightValue(Interpreter*) const;
private:
    NumericExpression* left;
    NumericExpression* right;
};

//less than boolean expression
class EqualExpression : public BooleanExpression {
public:
    EqualExpression(NumericExpression* left, NumericExpression* right);
    ~EqualExpression();
    virtual bool getValue(Interpreter*) const;
    virtual bool getValue(int,int) const;
    virtual std::string format() const;
    virtual std::string getLeftName(Interpreter*) const;
    virtual std::string getRightName(Interpreter*) const;
    //getting left and right values
    virtual int getLeftValue(Interpreter*) const;
    virtual int getRightValue(Interpreter*) const;
private:
    NumericExpression* left;
    NumericExpression* right;
};

#endif
