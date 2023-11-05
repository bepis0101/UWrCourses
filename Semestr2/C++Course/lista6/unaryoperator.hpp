#pragma once
#include "expression.hpp"
using namespace std;

class UnaryOperators : public Expression
{
    protected:
        Expression *l;
    public:
        virtual string record() = 0;
        virtual double evaluate() = 0;
};
class Sin : public UnaryOperators
{
    public:
        Sin(Expression *l);
        string record();
        double evaluate();
};
class Cos : public UnaryOperators
{
    public:
        Cos(Expression *l);
        string record();
        double evaluate();
};
class Exp : public UnaryOperators
{
    public:
        Exp(Expression *l);
        string record();
        double evaluate();
};
class Ln : public UnaryOperators
{
    public:
        Ln(Expression *l);
        string record();
        double evaluate();
};
class Abs : public UnaryOperators
{
    public:
        Abs(Expression *l);
        string record();
        double evaluate();
};
class Opposite : public UnaryOperators
{
    public:
        Opposite(Expression *l);
        string record();
        double evaluate();
};
class Inverse : public UnaryOperators
{
    public:
        Inverse(Expression *l);
        string record();
        double evaluate();
};