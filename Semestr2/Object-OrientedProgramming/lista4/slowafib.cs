/*
Borys Adamiak
Programowanie Obiektowe - Lista 4
Zadanie 2
mcs slowafib.cs ./slowafib.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;

class FibWords
{
    // string s;
    int x; // ostatni
    int curr; //aktualny
    public FibWords(int x)
    {
        this.x = x;
        curr = 0;
    }
    public FibWords(int x, int curr)
    {
        this.x = x;
        this.curr = curr;
    }
    string create(int x, string s)
    {
        if(x == 1)
        {
            s = "b";
            return s;
        }
        else if(x == 2)
        {
            s = "a";
            return s;
        }
        else
        {
            s = create(x-1, s) + create(x-2, s);
            return s;
        }
    }
    public FibWords next()
    {
        return new FibWords(x, curr+1);
    }
    public bool end()
    {
        return (curr > x);
    }
    public string val()
    {
        string s = "";
        return create(curr, s);
    }
    public void reset()
    {
        curr = 0;
    }
}

class Enum : IEnumerator
{
    FibWords f;
    public Enum(FibWords f)
    {
        this.f = f;
    }
    public object Current
    {
        get{
            return f.val();
        }
    }
    public void Reset()
    {
        f.reset();
    }
    public bool MoveNext()
    {
        f = f.next();
        if(f.end()) return false;
        return true;
    }
}
class WordsFib : IEnumerable
{
    FibWords f;
    public WordsFib(int x)
    {
        f = new FibWords(x);
    }
    public IEnumerator GetEnumerator()
    {
        return new Enum(f);
    }
}



class Program
{
    public static void Main()
    {
        WordsFib s = new WordsFib(12);
        foreach (string i in s)
        {
            Console.WriteLine(i);
        }
    }
}