#include "binaryoperator.hpp"
#include "constant.hpp"
#include "number.hpp"
#include "variable.hpp"

using namespace std;

int main()
{
    Var* x = new Var("x");
    Var* y = new Var("y");
    Var::add("y", 0);
    Var::add("x", 0);
    Expression *a = new Div(new Mult(new Sub(x, new Number(1)), x), new Number(2));
    Expression *b = new Div(new Add(new Number(3), new Number(5)), new Add(new Number(2), new Mult(x, new Number(7))));
    Expression *c = new Sub(new Add(new Number(2), new Mult(x, new Number(7))), new Add(new Mult(y, new Number(3)), new Number(5)));
    Expression *d = new Div(new Cos(new Mult(new Add(x, new Number(1)), new pi())), new Exp(new Pow(x, new Number(2))));
    double tabx[5] = {0.0, 0.0, 0.5, 0.5, 1.0};
    double taby[5] = {0.0, 0.5, 0.0, 0.5, 1.0};
    for(int i = 0; i < 5; i++)
    {
        cout << "\n x = " << tabx[i]  ;
        Var::modify("x", tabx[i]);
        cout << "\n y = " << taby[i] << "\n";
        Var::modify("y", taby[i]);
        cout << a->record() << " = " << a->evaluate() << "\n";
        cout << b->record() << " = " << b->evaluate() << "\n";
        cout << c->record() << " = " << c->evaluate() << "\n";
        cout << d->record() << " = " << d->evaluate() << "\n";
    }

}