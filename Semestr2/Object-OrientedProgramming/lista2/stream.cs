/*
Borys Adamiak
Lista 2 Programowanie Obiektowe
kompilator mcs stream.cs a nastepnie ./stream.exe
zadanie 1
*/


using System;
using System.Collections;
using System.Collections.Generic;

class IntStream
{
    int cnt;
    bool eos;
    public IntStream()
    {
        cnt = 0;
        eos = false;
    }
    
    public int next()
    {
        cnt++;
        return cnt;
    }
    public bool eos()
    {
        return this.eos;
    }
    public void reset()
    {
        this.eos = false;
        cnt = 0;
    }
}

class PrimeStream : IntStream
{
    public PrimeStream()
    {
        
    }
}