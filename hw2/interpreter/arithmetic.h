#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <vector>


//base class
class NumericExpression {
public:
    NumericExpression(){}
    NumericExpression(int value);
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;
    int getValue() const;
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
    Variable(int value, std::string name);
    ~Variable();
    virtual std::string format() const;
private:
    std::string name;
};

//class for variable with a name and index
class ArrayVariable : public NumericExpression {
public:
    ArrayVariable(int value, int index, std::string name);
    ~ArrayVariable();
    virtual std::string format() const;
private:
    int index;
    std::string name;
};


//class for an addition numeric expression
class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

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

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


//Now working on making boolean expressions work
class BooleanExpression {
public:
    BooleanExpression(bool value);
    virtual ~BooleanExpression() {}
    virtual std::string format() const = 0;
    bool getValue() const;
protected:
    bool value;
};

//less than boolean expression
class LessExpression : public BooleanExpression {
public:
    LessExpression(NumericExpression* left, NumericExpression* right);
    ~LessExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

//less than boolean expression
class EqualExpression : public BooleanExpression {
public:
    EqualExpression(NumericExpression* left, NumericExpression* right);
    ~EqualExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

#endif
