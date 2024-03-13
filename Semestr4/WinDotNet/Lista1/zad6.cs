using System;

public class Calculator
{
    protected int l;
    public Calculator() { }
    public Calculator(int a)
    {
        l = a;
    }
    public int add(int a, int b)
    {
        Console.WriteLine("2 args int");
        return a + b;
    }
    public int add(int a, int b, int c)
    {
        Console.WriteLine("3 args int");
        return a + b + c;
    }
    public double add(double a, double b)
    {
        Console.WriteLine("2 args double");
        return a + b;
    }
    public int add(int a, int b, int c, int d)
    {
        Console.WriteLine("4 args int");
        return add(a, b) + add(c, d);
    }
}
public class ExtendedCalc : Calculator
{
    public ExtendedCalc(int a)
    {
        l = a;
    }
    public int sum()
    {
        int res = 0;
        for(int i = 1; i <= l; i++)
        {
            res = add(i, res);
        }
        return res;
    }
}
class Program6
{
    public static void Main(string[] args)
    {
        Calculator a = new();
        Console.WriteLine(a.add(1, 2));
        Console.WriteLine(a.add(1.2, 1.5));
        Console.WriteLine(a.add(1, 2, 3));
        Console.WriteLine(a.add(1, 2, 3, 4));
        ExtendedCalc b = new(3);
        Console.WriteLine(b.sum());
    }
}