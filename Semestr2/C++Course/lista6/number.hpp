#pragma once
#include "expression.hpp"
using namespace std;

class Number : public Expression
{
    private:
        double num;
    public:
        Number(double num);
        double evaluate();
        string record();
};