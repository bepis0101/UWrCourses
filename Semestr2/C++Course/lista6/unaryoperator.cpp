#include "unaryoperator.hpp"
using namespace std;

Sin::Sin(Expression *l)
{
    this->l = l;
}

string Sin::record()
{
    string s = "sin(";
    s += l->record();
    s += ")";
    return s;
}

double Sin::evaluate()
{
    return sin(l->evaluate());
}

Cos::Cos(Expression *l)
{
    this->l = l;
}

string Cos::record()
{
    string s = "cos(";
    s += l->record();
    s += ")";
    return s;
}

double Cos::evaluate()
{
    return cos(l->evaluate());
}

Exp::Exp(Expression *l)
{
    this->l = l;
}

string Exp::record()
{
    string s = "e^(";
    s += l->record();
    s += ")";
    return s;
}

double Exp::evaluate()
{
    return exp(l->evaluate());
}

Ln::Ln(Expression *l)
{
    this->l = l;
}

string Ln::record()
{
    string s = "ln(";
    s += l->record();
    s += ")";
    return s;
}

double Ln::evaluate()
{
    return log(l->evaluate());
}

Abs::Abs(Expression *l)
{
    this->l = l;
}

string Abs::record()
{
    string s = "|";
    s += l->record();
    s += "|";
    return s;
}

double Abs::evaluate()
{
    return abs(l->evaluate());
}

Opposite::Opposite(Expression *l)
{
    this->l = l;
}

string Opposite::record()
{
    string s = "-(";
    s += l->record();
    s += ")";
    return s;
}

double Opposite::evaluate()
{
    return -(l->evaluate());
}

Inverse::Inverse(Expression *l)
{
    this->l = l;
}

string Inverse::record()
{
    string s = "1/(";
    s += l->record();
    s += ")";
    return s;
}
double Inverse::evaluate()
{
    return 1/(l->evaluate());
}
