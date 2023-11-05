#pragma once
#include "expression.hpp"
using namespace std;

class Constant : public Expression
{
    public:
        virtual double evaluate() = 0;
        virtual string record() = 0;
};

class pi : public Constant
{
    private:
        const double pi = M_PI;
    public:
        double evaluate();
        string record();
};
class fi : public Constant
{
    private:
        const double fi = 1.6180339887;
    public:
        double evaluate();
        string record();
};
class e : public Constant
{
    private:
        const double e = 2.718281828459;
    public:
        double evaluate();
        string record();
};