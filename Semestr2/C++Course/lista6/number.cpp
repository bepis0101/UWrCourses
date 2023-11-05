#include "number.hpp"
using namespace std;

Number::Number(double num)
{
    this->num = num;
}
double Number::evaluate()
{
    return num;
}
string Number::record()
{
    if(fmod(num, 1.0) == 0)
    {
        return to_string((int) num);
    }
    return to_string(num);
}