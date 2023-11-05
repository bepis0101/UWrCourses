#include "odcinek.hpp"
#include "structs.hpp"

const double epsilon = 0.00001;

segment::segment(point a, point b)
{
    if(a.wsp_x() == b.wsp_x() and a.wsp_y() == b.wsp_y())
    {
        throw invalid_argument("nie mozna utworzyc odicnka o dlugosci 0");
    }
    else
    {
        this->a = a;
        this->b = b;
    }
}
segment::segment(const segment& S)
{
    a = S.a;
    b = S.b;
}
void segment::translate(vec u)
{
    a.translate(u);
    b.translate(u);
}
void segment::turn_around(double angle)
{
    a.turn_around(angle);
    b.turn_around(angle);
}
void segment::cent_sym(point O)
{
    a.cent_sym(O);
    b.cent_sym(O);
}
double segment::length()
{
    return sqrt((b.wsp_x()-a.wsp_x())*(b.wsp_x()-a.wsp_x())+(b.wsp_y()-a.wsp_y())*(b.wsp_y()-a.wsp_y()));
}
void segment::ox_sym()
{
    a.ox_sym();
    b.ox_sym();
}
void segment::oy_sym()
{
    a.oy_sym();
    b.oy_sym();
}
point segment::A()
{
    return a;
}
point segment::B()
{
    return b;
}
bool segment::contain(point P)
{
    straight l = make(a, b);
    double x1 = a.wsp_x(), x2 = b.wsp_x();
    if(P.wsp_y() == l.a*P.wsp_x()+l.b and P.wsp_x() >= min(x1, x2) and P.wsp_x() <= max(x1, x2))
    {
        return true;
    }
    return false;
}
bool parallel(segment a, segment b)
{
    straight l, m;
    l = make(a.A(), a.B());
    m = make(b.A(), b.B());
    if(l.a == m.a) return true;
    return false;
}
bool perpendicular(segment a, segment b)
{
    straight l, m;
    l = make(a.A(), a.B());
    m = make(b.A(), b.B());
    if(l.a*m.a + 1 < epsilon) return true;
    return false;
}

bool intersect(segment a, segment b)
{
    straight l = make(a.A(), a.B());
    straight m = make(b.A(), b.B());
    // ax+b = cx+d <=> ax-cx = d-b
    if(l.a == m.a) return true;
    double x = (m.b-l.b)/(l.a-m.a);
    double y = m.a*x+m.b;
    point P(x, y);
    if(a.contain(P) and b.contain(P))
    {
        return true;
    }
    return false;
}
