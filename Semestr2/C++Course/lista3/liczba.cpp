#include "liczba.hpp"

using namespace std;

liczba::liczba() :  liczba(0){}

liczba::liczba(double num)
{
    elements = 1;
    current  = 0;
    memory = new double[memory_length];
    memory[current] = num;
}

liczba::liczba(liczba& other_num)
{
    add(other_num.get());
}

liczba& liczba::operator=(liczba& other_num)
{
    add(other_num.get());
    return *this;
}

liczba::liczba(liczba&& other_num)
{
    elements = other_num.elements;
    current = other_num.current;
    memory = other_num.memory;
    other_num.memory = nullptr;
}

liczba& liczba::operator=(liczba&& other_num)
{
    elements = other_num.elements;
    current = other_num.current;
    memory = other_num.memory;
    other_num.memory = nullptr;
    return *this;
}

liczba::~liczba()
{
    if(memory != nullptr)
    delete[] memory;
}


void liczba::add(double num)
{
    elements++;
    current++;
    memory[current%memory_length] = num;
}

const double liczba::get()
{
    return memory[current%memory_length];
}

const double liczba::get_past(int his)
{
    if(his > min(elements, memory_length)) throw invalid_argument("too far in history");
    return memory[((current-his)%memory_length)];
}

void liczba::revert(int his)
{
    if(his == 0) return;
    if(his > min(elements, memory_length)) throw invalid_argument("too far in history");
    add(memory[((current-his)%memory_length)]);
}