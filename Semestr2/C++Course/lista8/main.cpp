#include "rational.hpp"
using namespace std;
using namespace calculations;

int main()
{
    Rational oneTwelvth = Rational(1, 12);
    Rational threeSeventh = Rational(3, 7);
    Rational fiveThird = Rational(5, 3);
    Rational four = Rational(4);
    cout << oneTwelvth << threeSeventh << fiveThird << four;
    cout << (int)four << "\n";
    auto x = oneTwelvth/fiveThird;
    cout << x;
    x = four*threeSeventh;
    cout << x;
    double d = x;
    cout << d << "\n";
    x = threeSeventh + oneTwelvth;
    cout << x;
    x = x - four;
    cout << x;

    Rational a = Rational(2359348, 99900);
    cout << a;
}
