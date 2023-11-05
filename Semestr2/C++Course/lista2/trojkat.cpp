#include "trojkat.hpp"

triangle::triangle(point a, point b, point c)
{
    // y = (ya-yb)/(xa-xb) + (ya-(ya-yb)/(xa-xb)*xa)
    straight l = make(a, b);
    if(c.wsp_x()*l.a + l.b == c.wsp_y())
    {
        throw invalid_argument("trojkat nie moze miec punktow polozonych na jednej prostej");
    }
    else
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
}
triangle::triangle(const triangle& T)
{
    a = T.a;
    b = T.b;
    c = T.c;
}
void triangle::translate(vec u)
{
    a.translate(u);
    b.translate(u);
    c.translate(u);
}
void triangle::turn_around(double angle)
{
    a.turn_around(angle);
    b.turn_around(angle);
    c.turn_around(angle);
}
void triangle::cent_sym(point O)
{
    a.cent_sym(O);
    b.cent_sym(O);
    c.cent_sym(O);
}
void triangle::ox_sym()
{
    a.ox_sym();
    b.ox_sym();
    c.ox_sym();
}
void triangle::oy_sym()
{
    a.oy_sym();
    b.oy_sym();
    c.oy_sym();
}
double triangle::area()
{
    return (double)(abs((b.wsp_x()-a.wsp_x())*(c.wsp_y()-a.wsp_y())-(b.wsp_y()-a.wsp_y())*(c.wsp_x()-a.wsp_x())));
}
double triangle::circuit()
{
    segment a(this->a, this->b);
    segment b(this->b, this->c);
    segment c(this->a, this->c);
    return a.length()+b.length()+c.length();
}


bool triangle::is_in(point P)
{
    // with help of chat GPT
    vec AB, AC, AP;
    AB.x = b.wsp_x()-a.wsp_x(); AB.y = b.wsp_y()-a.wsp_y();
    AC.x = c.wsp_x()-a.wsp_x(); AC.y = c.wsp_y()-a.wsp_y();
    AP.x = P.wsp_x()-a.wsp_x(); AP.y = P.wsp_y()-a.wsp_y();
    double first = AB.x*AP.y-AB.y*AP.x, second = AC.x*AP.y-AC.y*AP.x;
    if(first*second > 0) return true;
    return false;
}
point triangle::A()
{
    return a;
}
point triangle::B()
{
    return b;
}

point triangle::C()
{
    return c;
}
bool separate(triangle T, triangle T1)
{
    point A, B, C, D, E, F;
    A = T.A();
    B = T.B();
    C = T.C();
    D = T1.A();
    E = T1.B();
    F = T1.C();
    segment AB = segment(A, B);
    segment AC = segment(A, C);
    segment BC = segment(B, C);
    segment DE = segment(D, E);
    segment EF = segment(E, F);
    segment DF = segment(D, F);
    bool check = intersect(AB, DE) and intersect(AB, EF) and intersect(AB, DF) and intersect(AC, DE) and intersect(AC, EF) and intersect(AC, DF) and intersect(BC, DE) and intersect(BC, EF) and intersect(BC, DF);
    return !(check);
}
bool contain(triangle T, triangle T1)
{
    // does T contain T1
    double x = (T1.A().wsp_x() + T1.B().wsp_x() + T1.C().wsp_x())/3;
    double y = (T1.A().wsp_y() + T1.B().wsp_y() + T1.C().wsp_y())/3;
    point P(x, y);
    if(T.is_in(P) and separate(T, T1));
}