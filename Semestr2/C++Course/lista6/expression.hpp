#pragma once
#include <bits/stdc++.h>
using namespace std;

class Expression
{
    public:
        virtual double evaluate() = 0;
        virtual string record() = 0;
};