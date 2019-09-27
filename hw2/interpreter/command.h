#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "arithmetic.h"

#include <string>

//base class for all commands to derive from
class Command {
public:
    Command(int line);
    virtual ~Command(){}
    virtual std::string format() const = 0;
    int getLine() const;
private:
    int line_number;
};

//class for print command
class PrintCommand : public Command {
public:
    PrintCommand(int line, NumericExpression* output);
    ~PrintCommand();
    virtual std::string format() const;
private:
    NumericExpression* output;
};

//class for Let command
class LetCommand : public Command {
public:
    LetCommand(int line, NumericExpression* setValue, 
        NumericExpression* variable);
    ~LetCommand();
    virtual std::string format() const;
private:
    NumericExpression* setValue;
    NumericExpression* variable;
};

//class for Let array command
class LetArrayCommand : public Command {
public:
    LetArrayCommand(int line, NumericExpression* setValue, 
        ArrayVariable* variable);
    ~LetArrayCommand();
    virtual std::string format() const;
private:
    NumericExpression* setValue;
    ArrayVariable* variable;
};

//class for goto command
class GoToCommand : public Command {
public:
    GoToCommand(int line, int destination);
    ~GoToCommand();
    virtual std::string format() const;
private:
    int destination;
};

//class for if then command
class IfThenCommand : public Command {
public:
    IfThenCommand(int line, BooleanExpression* conditional, int destination);
    ~IfThenCommand();
    virtual std::string format() const;
private:
    BooleanExpression* conditional;
    int destination;
};

//class for gosub command
//this class is similar to go to and will use line number data member
//to remember where it came from
//difference will happen when function for execution is later implemented
//other difference is in string output function
class GoSubCommand : public Command {
public:
    GoSubCommand(int line, int destination);
    ~GoSubCommand();
    virtual std::string format() const;
private:
    int destination;
};

//class for return command
class ReturnCommand : public Command {
public:
    ReturnCommand(int line);
    ~ReturnCommand();
    virtual std::string format() const;
};


//class for end command
class EndCommand : public Command {
public:
    EndCommand(int line);
    ~EndCommand();
    virtual std::string format() const;
};

#endif
