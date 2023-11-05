#pragma once 
#include "color.hpp"
#include <bits/stdc++.h>

using namespace std;
struct vec
{
    int x, y;
};
class pixel
{
    protected:
        int x;
        int y;
        static int size_x;
        static int size_y;
    public:
        pixel(int x, int y);
        int from_left();
        int from_right();
        int from_top();
        int from_bottom();
        void check_pixels();
        int get_x() const;
        int get_y() const;
        int calc_dist(int x, int y) const;
        friend ostream &operator<< (ostream &out, const pixel &c);
};
class colored_pixel : public pixel, public transparent_color
{
    public:
        colored_pixel(colorval red, colorval green, colorval blue, colorval alfa, int x, int y);
        void move(vec v);
        friend ostream &operator<< (ostream &out, const colored_pixel &c);
};
int pix_dist(const pixel &p, const pixel &q);
int pix_dist(const pixel *p, const pixel *q);