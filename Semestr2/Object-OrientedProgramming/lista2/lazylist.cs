/*
Borys Adamiak
Lista 2 Programowanie Obiektowe
kompilator mcs lazylist.cs a nastepnie ./lazylist.exe
zadanie 4
*/


using System;
using System.Collections;
using System.Collections.Generic;


class LazyList
{
    List <int> L;
    int size;

    public LazyList()
    {
        L = new List<int>();
        size = 0;
    }
    public int element(int el)
    {
        if(el > size)
        {
            for(int i = size+1; i <= el; i++)
            {
                L.Add(i);
            }
            size = el;
        }
        return L[el-1];
    }
}

class LazyPrimeList : LazyList
{
    List <int> Lprime;
    int sizeP;
    public LazyPrimeList()
    {
        Lprime = new List<int>();
        sizeP = 0;
    }
    bool is_prime(int x)
    {
        if(x == 1 || x == 0)
        {
            return false;
        }
        for(int i = 2; i < x; i++)
        {
            if(x % i == 0) return false;
        }
        return true;
    }

    public int prime_element(int el)
    {
        int last;
        if(sizeP == 0) last = 1;
        else last = Lprime[sizeP-1];
        while(el > sizeP)
        {
            if(is_prime(last+1) == true)
            {
                Lprime.Add(last+1);
                sizeP++;
                last = Lprime[sizeP-1];
            }
            else
            {
                last++;
            }
        }
        return Lprime[el-1];
    }
}

class Program
{
    
    public static void Main()
    {
        LazyList lista = new LazyList();
        Console.WriteLine(lista.element(30));
        lista.element(45);
        lista.element(15);
        LazyPrimeList list = new LazyPrimeList();
        Console.WriteLine(list.prime_element(10));
    }
}