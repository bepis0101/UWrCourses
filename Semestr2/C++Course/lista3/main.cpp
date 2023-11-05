#include "liczba.hpp"
using namespace std;

int main()
{
    liczba x = liczba();
    x.add(5);
    x.add(4);
    x.add(4);
    x.add(12);
    x.add(15);
    cout << x.get() << endl;
    cout << x.get_past(5) << endl; 
    cout << x.get_past(3) << endl;

    liczba a = liczba(5);
    liczba b;
    a.add(3);
    a.add(2);
    b = a;
    cout << b.get() << endl;
    liczba c;
    c = move(b);
    cout << c.get() << endl;
    c.add(3);
    c.add(4);
    cout << c.get_past(1) << endl;
    c.revert(2);
    cout << c.get();
    cerr << x.get_past(10) << endl;
}