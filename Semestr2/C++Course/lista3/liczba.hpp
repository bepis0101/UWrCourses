#ifndef LICZBA_HPP
#define LICZBA_HPP
#include <bits/stdc++.h>
using namespace std;

class liczba
{
    private:
        const int memory_length = 5;
        int elements;
        int current;
        double* memory;

    public:
        liczba();
        liczba(double num);
        liczba(liczba& other_num);
        liczba& operator=(liczba& other_num);
        liczba(liczba&& other_num);
        liczba& operator=(liczba&& other_num);
        ~liczba();
        void add(double num);
        const double get();
        const double get_past(int his);
        void revert(int his);
};


#endif