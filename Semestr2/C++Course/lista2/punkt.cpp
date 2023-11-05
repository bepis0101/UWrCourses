#include "punkt.hpp"
point::point(double x, double y)
{
    this->x = x;
    this->y = y;
}
point::point()
{
    x = y = 0; 
}
point::point(const point& P)
{
    x = P.x;
    y = P.y;
}
void point::translate(vec u)
{
    this->x += u.x;
    this->y += u.y;
}
double point::wsp_x()
{
    return x;
}
double point::wsp_y()
{
    return y;
}
double point::distance(point p)
{
    return sqrt((x-p.wsp_x())*(x-p.wsp_x())+(y-p.wsp_y())*(y-p.wsp_y()));
}
void point::turn_around(double angle)
{
    angle = (angle*M_PI)/180;
    x = x*cos(angle) - y*sin(angle);
    y = x*sin(angle) + y*cos(angle);
}
void point::cent_sym(point O)
{
    x = 2*O.wsp_x() - x;
    y = 2*O.wsp_y() - y;
}
void point::ox_sym()
{
    x *= (-1);
}
void point::oy_sym()
{
    y *= (-1);
}
double length(point a, point b)
{
    return sqrt((b.wsp_x()-a.wsp_x())*(b.wsp_x()-a.wsp_x())+(b.wsp_y()-a.wsp_y())*(b.wsp_y()-a.wsp_y()));
}
straight make(point a, point b)
{
    // 
    straight l;
    l.a = (a.wsp_y()-b.wsp_y())/(a.wsp_x()-b.wsp_x());
    l.b = (a.wsp_y()-((a.wsp_y()-b.wsp_y())/(a.wsp_x()-b.wsp_x()))*a.wsp_x());
    return l;
}