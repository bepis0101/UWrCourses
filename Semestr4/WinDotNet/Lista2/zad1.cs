static class A
{
    //only static members
    //cant be instantiated
    //is sealed (aka u cant inherit)
    //cant contain public constructors
    public static int n;
}

sealed class B // cant inherit
{
    public static int n;
}

abstract class C
{
    abstract public int doSth(); // for interfaces
}

class D
{
    virtual public int log(int x)
    {
        return x;
    }
}
// we have virtual members and we want to override them
// in inherited class we need to use "override" kewyword
class E : D
{
    override public int log(int x)
    {
        return 1 - x;
    }
}

partial class F
{
    public static int n;
}
partial class F
{
    public void f(in int x) // in is readonly
    {
        F.n = x;
    }
}

class G
{
    public readonly int n;
    G(int n)
    {
        this.n = n;
    }
    void f(ref int x) // jak referencja w C++
    {
        x *= 2;
        //n = x error
    }


}

class H
{
    int a, b;
    void f(out int l, out int r)
    {
        l = 2;
        r = 3;
        // out: variable must be changed before end of function scope
    }
}

//params is for list of arguments

public class Program
{
    public static void Main1(string[] args)
    {
        A.n = 10;
        Console.WriteLine(A.n);
    }
}