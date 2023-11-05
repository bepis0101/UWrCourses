#ifndef ODCINEK_HPP
#define ODCINEK_HPP
#include "punkt.hpp"

class segment
{
    private:
        point a, b;
    public:
        segment(point a, point b);
        segment(const segment& S);
        void translate(vec u);
        void turn_around(double angle);
        void cent_sym(point O);
        double length();
        void oy_sym();
        void ox_sym();
        point A();
        point B();
        bool contain(point P);
};

bool parallel(segment a, segment b);
bool perpendicular(segment a, segment b);
bool intersect(segment a, segment b);
#endif