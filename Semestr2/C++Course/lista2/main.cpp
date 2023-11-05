#include "punkt.hpp"
#include "odcinek.hpp"
#include "trojkat.hpp"

using namespace std;

int main()
{
    point A = point(1, 5);
    point B = point(6, -2);
    segment AB = segment(A, B);
    segment BA = segment(AB);
    A.turn_around(50);
    vec u; u.x = 4; u.y = 1;
    A.translate(u);
    B.cent_sym(A);
    AB = segment(A, B);
    BA = segment(AB);
    BA.turn_around(90);
    if(parallel(AB, BA)) cout << "Odcinki AB i BA sa rownlolegle\n";
    if(perpendicular(AB, BA)) cout << "Odcinki AB i BA sa prostopadle\n";
    point C = point(6, 6);
    segment AC = segment(A, C);
    segment BC = segment(B, C);
    triangle ABC = triangle(A, B, C);
    cout << "Trojkat ABC o punktach:\n";
    cout << "A:(" << A.wsp_x() << ", " << A.wsp_y() << ") ";
    cout << "B:(" << B.wsp_x() << ", " << B.wsp_y() << ") ";
    cout << "C:(" << C.wsp_x() << ", " << C.wsp_y() << ")\n";
    cout << "Ma pole " << ABC.area() << " i obwod " << ABC.circuit();
    point O = point(10, 12);
    ABC.cent_sym(O);
    cout << "\nTrojkat ABC po wykonaniu symetri srodkowej wobec puntku O(" << O.wsp_x() << ", " << O.wsp_y() << "):\n";
    cout << "A:(" << (ABC.A()).wsp_x() << ", " << (ABC.A()).wsp_y() << ") ";
    cout << "B:(" << (ABC.B()).wsp_x() << ", " << (ABC.B()).wsp_y() << ") ";
    cout << "C:(" << (ABC.C()).wsp_x() << ", " << (ABC.C()).wsp_y() << ")\n";
    triangle DEF = triangle(ABC);
    vec v; v.x = -13; v.y = -20;
    DEF.translate(v);
    cout << "Trojkat DEF to trojkat ABC po translacji o wektor v = [-13, -20]\nJego punkty to:\n";
    cout << "D:(" << (DEF.A()).wsp_x() << ", " << (DEF.A()).wsp_y() << ") ";
    cout << "E:(" << (DEF.B()).wsp_x() << ", " << (DEF.B()).wsp_y() << ") ";
    cout << "F:(" << (DEF.C()).wsp_x() << ", " << (DEF.C()).wsp_y() << ")\n";
    DEF.ox_sym();
    DEF.oy_sym();
    cout << "Trojkat DEF po nalozeniu na niego symetri osiowej wzgledem osi OX i OY:\n";
    cout << "D:(" << (DEF.A()).wsp_x() << ", " << (DEF.A()).wsp_y() << ") ";
    cout << "E:(" << (DEF.B()).wsp_x() << ", " << (DEF.B()).wsp_y() << ") ";
    cout << "F:(" << (DEF.C()).wsp_x() << ", " << (DEF.C()).wsp_y() << ")\n";
    point P = point(-3.5, 2);
    if(DEF.is_in(P)) cout << "Punkt P(" << P.wsp_x() << ", " << P.wsp_y() << ") zawiera sie w trojkacie DEF\n"; 
    if(contain(ABC, DEF) == true) cout << "Trojakt ABC zawiera trojkat DEF\n";
    else if(separate(ABC, DEF) == true) cout << "Trojkaty ABC i DEF sa rozlaczne\n";
    else cout << "Trojkaty ABC i DEF sie przecinaja\n";
}