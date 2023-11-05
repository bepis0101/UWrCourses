#include "color.hpp"
using namespace std;

color::color()
{
    red = green = blue = 0;
}
color::color(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    check(red, green, blue);
}
void color::set_red(int red)
{
    *this = color(red, green, blue);
}
void color::set_blue(int blue)
{
    *this = color(red, green, blue);
}
void color::set_green(int green)
{
    *this = color(red, green, blue);
}
void transparent_color::set_transparency(colorval alfa)
{
    this->alfa = alfa;
    if(alfa < 0 or alfa > 255) throw invalid_argument("wrong argument");
}
void color::brighten(colorval bright)
{
    *this = color(red+bright, green+bright, blue+bright);
}
void color::darken(colorval dark)
{
    *this = color(red-dark, green-dark, blue-dark);
}
void color::check(int red, int green, int blue)
{
    if(red < 0 or red > 255) throw invalid_argument("wrong args");
    if(blue < 0 or blue > 255) throw invalid_argument("wrong args");
    if(green < 0 or green > 255) throw invalid_argument("wrong args");
}
void check_string(string name)
{
    for(auto c : name)
    {
        if(c < 'a' or c > 'z')
        throw invalid_argument("name must consist of small letters only");
    }
}
transparent_color::transparent_color(colorval red, colorval green, colorval blue, colorval alfa) : color(red, green, blue)
{set_transparency(alfa);}
named_color::named_color(colorval red, colorval green, colorval blue) : color(red, green, blue){}
void named_color::set_name(string name) 
{
    check_string(name);
    this->name = name;
}
ntcolor::ntcolor(colorval red, colorval green, colorval blue, string name, colorval alfa)
: transparent_color(red, green, blue, alfa), named_color(red, green, blue) {set_name(name);}

colorval color::combine(colorval col, colorval col2) {return (col+col2)/2;}

ostream &operator<< (ostream &out, const color &c)
{
    return out << "[" << c.get_red() << ' ' << c.get_green() << ' ' << c.get_blue() << "]\n";
}
ostream &operator<< (ostream &out, const named_color &c)
{
    return out << "[" << c.get_red() << ' ' << c.get_green() << ' ' << c.get_blue() << ' ' << c.get_name() <<  "]\n";
}

ostream &operator<< (ostream &out, const transparent_color &c)
{
    return out << "[" << c.get_red() << ' ' << c.get_green() << ' ' << c.get_blue() << ' ' << c.get_transparency() <<  "]\n";
}
ostream &operator<< (ostream &out, const ntcolor &c)
{
    return out << "[" << c.get_red() << ' ' << c.get_green() << ' ' << c.get_blue() << ' ' << c.get_name() << c.get_transparency() <<  "]\n";
}