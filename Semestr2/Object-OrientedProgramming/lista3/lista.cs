/*
Borys Adamiak
Lista 3 Programowanie Obiektowe
Zadanie 1
mcs -reference:list-lib.dll lista.cs
./lista.exe
*/
using System;

class Program
{
    public static void Main()
    {
        List<int> L  = new List<int>();
        L.push_back(1);
        L.push_back(3);
        L.push_front(2);
        Console.WriteLine(L.pop_back());
        Console.WriteLine(L.pop_back());
        Console.WriteLine(L.pop_back());
        L.push_back(1);
        L.push_back(3);
        L.push_front(2);
        Console.WriteLine(L.pop_front());
        Console.WriteLine(L.pop_front());
        Console.WriteLine(L.pop_front());
        Console.WriteLine(L.pop_back());
    }
}