#ifndef PUNKT_HPP
#define PUNKT_HPP
#include "structs.hpp"

using namespace std;

class point
{
    private:
        double x, y;
    
    public:
        point(double x, double y);
        point();
        point(const point &P);
        void translate(vec u);
        double wsp_x();
        double wsp_y();
        double distance(point p);
        void turn_around(double angle);
        void cent_sym(point O);
        void oy_sym();
        void ox_sym();
};

double length(point a, point b);
straight make(point a, point b);
#endif