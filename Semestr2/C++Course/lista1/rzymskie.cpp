#include <bits/stdc++.h>

using namespace std;

const vector<pair <int, string> > rzymskie = {
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

string bin2rzym(int x)
{
    string s = "";
    int pointer = 0;
    while(x > 0)
    {
        if(x >= rzymskie[pointer].first)
        {
            s += rzymskie[pointer].second;
            x -= rzymskie[pointer].first;
        }
        else
        {
            pointer++;
        }
    }
    return s;
}

int main(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        int x;
        try {
            x = stoi(argv[i], nullptr, 10);
            if (x < 1 or x >= 4000) throw 1;
        }
        catch(...)
        {
            clog << "Blad wejscia\n";
            continue;
        }
        cout << bin2rzym(x) << "\n";
    }
}