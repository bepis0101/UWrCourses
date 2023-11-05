#pragma once
#include "expression.hpp"
using namespace std;

class Var : public Expression
{
    private:
        string var;
        static vector< pair<string, double> > variables;
    public:
        Var(string var);
        double evaluate();
        string record();
        static void add(string var, double val);
        static void delete_var(string var);
        static void modify(string var, double val);
        static double get(string var);
};