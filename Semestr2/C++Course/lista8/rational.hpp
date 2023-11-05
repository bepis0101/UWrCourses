#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace calculations
{
    class Rational
    {
        private:
            int nom;
            int denom;
        public:
            Rational(int nom, int denom);
            Rational();
            Rational(int nom);
            int getNom();
            int getDenom();
            
            Rational operator+(const Rational& other);
            Rational operator-(const Rational& other);
            Rational operator*(const Rational& other);
            Rational operator/(const Rational& other);
            Rational operator!();
            Rational operator-();
            operator double();
            explicit operator int();
            string toString() const;
            // friend ostream& operator<<(ostream &out, Rational r);
    };

    class RationalException : public logic_error
    {
        public:
            RationalException(const string& what_arg) : logic_error(what_arg){};
    };
    class DivisionByZero : public RationalException
    {
        public:
            DivisionByZero(const string& what_arg) : RationalException(what_arg){}
    };
    class OutOfRange : public RationalException
    {
        public:
            OutOfRange(const string& what_arg) : RationalException(what_arg){}
    };
};
ostream& operator<<(ostream &out, calculations::Rational r);