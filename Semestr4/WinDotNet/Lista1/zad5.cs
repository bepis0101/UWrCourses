using System;
using System.Runtime.InteropServices;

public class A
{
    public int a; // public on all 
    private int b; // only accesible inside a class
    protected int c; // accesible inside a class and its children
    internal int d; // accessible inside a scope
    public A()
    {
        a = 1;
        b = 2;
        c = 3;
        d = 4;
    }
    public void print()
    {
        Console.WriteLine(a);
        Console.WriteLine(b);
        Console.WriteLine(c);
        Console.WriteLine(d);
    }
}

class B : A
{
    public void printprotected()
    {
        Console.WriteLine(this.c);
    }
}

public class Program5
{
    public static void Main5(string[] args)
    {
        A a = new();
        B b = new();
        a.print();
        //b.print(); error cause b is private 
        //Console.WriteLine(b.c) outside of inherited class
        b.printprotected();
        Console.WriteLine(b.d);
    }
}