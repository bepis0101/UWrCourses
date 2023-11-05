#include "rational.hpp"
using namespace std;
using namespace calculations;

Rational::Rational(int nom, int denom)
{
    if(denom == 0) throw DivisionByZero("cant divide by zero");
    int nwd = gcd(nom, denom);
    nom /= nwd;
    denom /= nwd;
    if(denom < 0)
    {
        this->nom = -nom;
        this->denom = -denom;
    }
    else
    {
        this->nom = nom;
        this->denom = denom;
    }
}
Rational::Rational() : Rational(0, 1) {}

Rational::Rational(int num) : Rational(num, 1){}

int Rational::getNom() { return nom; }

int Rational::getDenom() { return denom; }

Rational Rational::operator+(const Rational& other)
{
    if((long long)nom*other.denom + other.nom*denom > INT_MAX or (long long) denom*other.denom > INT_MAX)
    {
        throw OutOfRange("Out of int range");
    }
    if((long long)nom*other.denom + other.nom*denom < INT_MIN or (long long) denom*other.denom < INT_MIN)
    {
        throw OutOfRange("Out of int range");
    }
    return Rational(nom*other.denom + other.nom*denom, denom*other.denom);
}


Rational Rational::operator-(const Rational& other)
{
    if((long long)nom*other.denom - other.nom*denom > INT_MAX or (long long)denom*other.denom > INT_MAX)
    {
        throw OutOfRange("Out of int range");
    }
    if((long long)nom*other.denom + other.nom*denom < INT_MIN or (long long) denom*other.denom < INT_MIN)
    {
        throw OutOfRange("Out of int range");
    }
    
    return Rational(nom*other.denom - other.nom*denom, denom*other.denom);
}

Rational Rational::operator*(const Rational& other)
{
    if((long long)nom*other.nom > INT_MAX or (long long)other.denom*denom > INT_MAX)
    {
        throw OutOfRange("Out of int range");
    }
    if((long long)nom*other.nom < INT_MIN)
    {
        throw OutOfRange("Out of int range");
    }
    return Rational(nom*other.nom, other.denom*denom);
}

Rational Rational::operator/(const Rational& other)
{
    if((long long)nom*other.denom > INT_MAX or (long long)other.nom*denom > INT_MAX)
    {
        throw OutOfRange("Out of int range");
    }
    if((long long)nom*other.denom < INT_MIN or (long long)other.nom*denom < INT_MIN)
    {
        throw OutOfRange("Out of int range");
    }
    
    return Rational(nom*other.denom, other.nom*denom);
}

Rational Rational::operator!()
{
    return Rational(denom, nom);
}

Rational Rational::operator-()
{
    return Rational(-nom, denom);
}

Rational::operator double()
{
    return (double)nom/denom;
}

Rational::operator int()
{
    return (int)(nom/denom);
}

string Rational::toString() const
{
    int integral = nom/denom;
    string res = to_string(integral);
    if(denom != 1)
    {
        res += '.';

        map <int, int> m;
        int r = abs(nom) % denom;
        while(r != 0 and m.find(r) == m.end())
        {
            m[r] = res.length();
            r *= 10;
            res += to_string(r / denom);
            r %= denom;
        }

        if(r)
        {
            res.insert(m[r], "(");
            res += ")";
        }
    }

    return res;
}

ostream& operator<<(ostream &out, Rational r)
{
    string s = r.toString();
    return out << s << "\n";
}