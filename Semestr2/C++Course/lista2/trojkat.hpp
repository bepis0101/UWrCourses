#ifndef TROJKAT_HPP
#define TROJKAT_HPP
#include "odcinek.hpp"

class triangle
{
    private:
        point a, b, c;
    
    public:
        triangle(point a, point b, point c);
        triangle(const triangle &T);
        void translate(vec u);
        void turn_around(double angle);
        void cent_sym(point O);
        void oy_sym();
        void ox_sym();
        double area();
        double circuit();
        bool is_in(point P);
        point A();
        point B();
        point C();
};

bool contain(triangle T, triangle T1);
bool separate(triangle T, triangle T1);
#endif