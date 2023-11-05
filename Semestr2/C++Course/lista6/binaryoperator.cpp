#include "binaryoperator.hpp"
using namespace std;

Add::Add(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;   
}

double Add::evaluate()
{
    return l->evaluate() + r->evaluate();
}

string Add::record()
{
    string s = "(";
    s += l->record();
    s += "+";
    s += r->record();
    s += ")";
    return s;
}

Sub::Sub(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Sub::evaluate()
{
    return l->evaluate() - r->evaluate();
}

string Sub::record()
{
    string s = "(";
    s += l->record();
    s += "-";
    s += r->record();
    s += ")";
    return s;
}

Log::Log(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Log::evaluate()
{
    return log(r->evaluate())/log(l->evaluate());
}

string Log::record()
{
    string s = "(";
    s += l->record();
    s += ")(";
    s += r->record();
    s += ")";
    return s;
}

Mod::Mod(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Mod::evaluate()
{
    return fmod(l->evaluate(), r->evaluate());
}

string Mod::record()
{
    string s = l->record();
    s += "%";
    s += r->record();
    return s;
}

Mult::Mult(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Mult::evaluate()
{
    return l->evaluate() * r->evaluate();
}

string Mult::record()
{
    string s = l->record();
    s += "*";
    s += r->record();
    return s;
}

Div::Div(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Div::evaluate()
{
    if(r->evaluate() == 0)
    {
        throw invalid_argument("cant div by 0");
    }
    double x = l->evaluate() / r->evaluate();
    return x;
}

string Div::record()
{
    string s = l->record();
    s += "/";
    s += r->record();
    return s;
}

Pow::Pow(Expression *l, Expression *r)
{
    this->l = l;
    this->r = r;
}

double Pow::evaluate()
{
    return pow(l->evaluate(), r->evaluate());
}

string Pow::record()
{
    string s = l->record();
    s += "^";
    s += r->record();
    return s;
}