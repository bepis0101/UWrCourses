#pragma once
#include "unaryoperator.hpp"
using namespace std;

class BinaryOperators : public UnaryOperators
{
    protected:
        Expression *r;
    public:
        virtual double evaluate() = 0;
        virtual string record() = 0;
};

class Add : public BinaryOperators
{
    public:
        Add(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Sub : public BinaryOperators
{
    public:
        Sub(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Log : public BinaryOperators
{
    public:
        Log(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Mod : public BinaryOperators
{
    public:
        Mod(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Mult : public BinaryOperators
{
    public:
        Mult(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Div : public BinaryOperators
{
    public:
        Div(Expression *l, Expression *r);
        double evaluate();
        string record();
};

class Pow : public BinaryOperators
{
    public:
        Pow(Expression *l, Expression *r);
        double evaluate();
        string record();
};