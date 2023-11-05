#include <bits/stdc++.h>
using namespace std;
class Rational {
public:
    int nom, denom;
    Rational(int nom, int denom)
    {
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
    Rational() : Rational(0, 1) {}

    Rational(int num) : Rational(num, 1){}

    int getNom() { return nom; }

    int getDenom() { return denom; }

    Rational operator+(const Rational& other)
    {
        return Rational(nom*other.denom + other.nom*denom, denom*other.denom);
    }


    Rational operator-(const Rational& other)
    {
        return Rational(nom*other.denom - other.nom*denom, denom*other.denom);
    }

    Rational operator*(const Rational& other)
    {
        return Rational(nom*other.nom, other.denom*denom);
    }

    Rational operator/(const Rational& other)
    {
        return Rational(nom*other.denom, other.nom*denom);
    }

    Rational operator!()
    {
        return Rational(denom, nom);
    }

    Rational operator-()
    {
        return Rational(-nom, denom);
    }

    operator double()
    {
        return (double)nom/denom;
    }

    operator int()
    {
        return (int)(nom/denom);
    }

    string toString() const
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
};
ostream& operator<<(ostream &out, Rational r)
{
    string s = r.toString();
    return out << s << ' ';
}

Rational pow_fraction(int n) {
    Rational res(1);
    if(n < 0) res.denom = pow(2, -n);
    else res.nom = pow(2, n);
    return res;
}

void print(int cecha) {
    int i = 0b10000;
    Rational cecha_frac = pow_fraction(cecha);

    cout << "Cecha: " << cecha << "\n";
    while(i < 0b100000) {
        auto f = Rational(i, pow(2, 5)) * cecha_frac;
        cout << f << f.nom << '/' << f.denom <<'\n';
        i++;
    }

    cout << '\n';
}

int main() {
    for(int i : {-1, 0, 1}) {
        print(i);
    }
}