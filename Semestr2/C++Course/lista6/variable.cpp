#include "variable.hpp"
using namespace std;

Var::Var(string var)
{
    this->var = var;
}
double Var::evaluate()
{
    return get(this->var);
}
string Var::record()
{
    return var;
}
void Var::add(string var, double val)
{
    variables.push_back({var, val});
}
void Var::delete_var(string var)
{
    int pos = -1;
    for(int i = 0; i < variables.size(); i++)
    {
        if(variables[i].first == var)
        {
            pos = i;
            break;
        }
    }
    if(pos == -1) throw invalid_argument("variable doesn't exist");
    variables.erase(variables.begin()+pos);
}
void Var::modify(string var, double val)
{
    for(int i = 0; i < variables.size(); i++)
    {
        if(variables[i].first == var)
        {
            variables[i].second = val;
        }
    }
}
double Var::get(string var)
{
    for(int i = 0; i < variables.size(); i++)
    {
        if(variables[i].first == var)
        {
            return variables[i].second;
        }
    }
    throw invalid_argument("variable doesn't exist");
}
vector< pair<string, double> > Var::variables;