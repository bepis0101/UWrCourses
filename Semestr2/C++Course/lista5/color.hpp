#pragma once
#include <bits/stdc++.h>
#define colorval unsigned char


using namespace std;

class color
{
    protected:
        colorval red; 
        colorval green;
        colorval blue;
    public:
        color();
        color(int red, int green, int blue);
        inline int get_red() const {return red;}
        inline int get_blue() const {return blue;}
        inline int get_green() const {return green;}
        void set_red(colorval red);
        void set_green(colorval green);
        void set_blue(colorval blue);
        void brighten(colorval bright);
        void darken(colorval dark);
        void check(int r, int g, int b);
        static colorval combine(colorval col, colorval col2);
        friend ostream &operator<< (ostream &out, const color &c);
};
class transparent_color : public virtual color
{
    protected:
        colorval alfa;
    public:
        transparent_color(colorval red, colorval green, colorval blue, colorval alfa);
        void set_transparency(colorval alfa);
        inline colorval get_transparency() const {return alfa;}
        friend ostream &operator<< (ostream &out, const transparent_color &c);
};
class named_color : public virtual color
{
    protected:
        string name = "";
    public:
        named_color(colorval red, colorval green, colorval blue);
        void set_name(string name);
        inline string get_name() const {return name;}
        friend ostream &operator<< (ostream &out, const named_color &c);
};

class ntcolor : public named_color, public transparent_color
{
    public:
        ntcolor(colorval red, colorval green, colorval blue, string name, colorval alfa);
        friend ostream &operator<< (ostream &out, const ntcolor &c);

};