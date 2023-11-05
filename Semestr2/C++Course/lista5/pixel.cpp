#include "pixel.hpp"
using namespace std;

pixel::pixel(int x, int y)
{
    if(x < 0 or x > size_x or y < 0 or y > size_y) throw invalid_argument("wrong args");
    this->x = x;
    this->y = y;   
}
int pixel::from_bottom()
{
    return y;
}
int pixel::from_left()
{
    return x;
}
int pixel::from_right()
{
    return size_x-x;
}
int pixel::from_top()
{
    return size_y-y;
}
int pixel::calc_dist(int x, int y) const
{
    return (int) sqrt((x-this->x)*(x-this->x) + (y-this->y)*(y-this->y));
}
int pixel::get_x() const {return x;}
int pixel::get_y() const {return y;}
int pixel::size_x = 1920;
int pixel::size_y = 1080;
void pixel::check_pixels()
{
    if(x < 0 or x > size_x or y < 0 or y > size_y) throw invalid_argument("wrong args");
}
colored_pixel::colored_pixel(colorval red, colorval green, colorval blue, colorval alfa, int x, int y) : 
                            pixel(x, y), transparent_color(red, green, blue, alfa){}

void colored_pixel::move(vec v)
{
    x += v.x;
    y += v.y;
    check_pixels();
}
int pix_dist(const pixel &p, const pixel &q)
{
    return q.calc_dist(p.get_x(), p.get_y());
}
int pix_dist(const pixel *p, const pixel *q)
{
    return q->calc_dist(p->get_x(), q->get_y());
}
ostream &operator<< (ostream &out, const pixel &c)
{
    return out << '[' << c.get_x() << ' ' << c.get_y() << ']' << '\n';
}
ostream &operator<< (ostream &out, const colored_pixel &c)
{
    return out << '[' << c.get_x() << ' ' << c.get_y() << ' '  << c.get_red() << ' ' 
        << c.get_green() << ' ' << c.get_blue() << ' ' << c.get_transparency() << ']' << '\n';
}