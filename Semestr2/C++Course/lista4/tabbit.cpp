#include "tabbit.hpp"
using namespace std;
tab_bit::tab_bit(int rozm)
{
    dl = rozm;
    tab = new slowo[rozm/(sizeof(slowo)*8)+1]
}
tab_bit::tab_bit(slowo tb)
{
    dl = sizeof(tb)*8;
    tab = new slowo[1];
}
tab_bit::tab_bit(const tab_bit &tb)
{
    dl = tb.dl;
    tab = tb.tab;
}
tab_bit::tab_bit(tab_bit &&tb)
{
    dl = tb.dl;
    tab = tb.tab;
    tb.tab = nullptr;
}
tab_bit & tab_bit::operator=(const tab_bit &tb)
{
    dl = tb.dl;
    tab = tb.tab;
    return *this;
}
tab_bit& tab_bit::operator=(tab_bit &&tb)
{
    dl = tb.dl;
    tab = tb.tab;
    tb.tab = nullptr;
    return *this;
}
tab_bit::~tab_bit()
{
    delete[] tab;
}
bool tab_bit::czytaj(int i) const
{
    if(i > dl)
    {
        throw invalid_argument("nie istnieje taki bit");
    }
    int which_word = i/(sizeof(i)*8);
    i %= (sizeof(i)*8);
    return (tab[which_word] & (1 << i));
}
bool tab_bit::pisz(int i, bool b)
{
    if(i > dl)
    {
        throw invalid_argument("nie istnieje taki bit");
    }
    int which_word = i/(sizeof(i)*8);
    i %= (sizeof(i)*8);
    if(b)
    {
        tab[which_word] |= (1 << i); // zapalenie bita
    }
    else
    {
        tab[which_word] &= ~(1 << i); //zgaszenie bita
    }
    return b;
}
bool tab_bit::operator[](int i) const
{
    if(i > dl)
    {
        throw invalid_argument("nie istnieje taki bit");
    }
    int which_word = i/(sizeof(i)*8);
    i %= (sizeof(i)*8);
    return (tab[which_word] & (1 << i));
}