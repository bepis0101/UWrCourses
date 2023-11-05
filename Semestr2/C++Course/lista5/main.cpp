#include "pixel.hpp"
#include "color.hpp"

using namespace std;

int main()
{
    color c(1, 2, 3);
    cout << c;
    transparent_color tc(4, 5, 6, 50);
    cout << tc;
    named_color nc(3, 4, 2);
    cout << nc;
    nc.set_name("czarny");
    cout << nc;
    ntcolor ntc(3, 2, 1, "czarnytransparentny", 22);
    pixel p(10, 27);
    colored_pixel cp(40, 200, 3, 2, 1, 22);
    cout << p << cp;
    cout << pix_dist(p, cp) << "\n";
    cout << p.from_bottom() << ' ' << p.from_top() << " "
    << p.from_left() << ' ' << p.from_right() << "\n";
    cp.move({10, 25});
    cout << cp;

}