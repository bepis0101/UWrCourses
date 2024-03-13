using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Finalizer
{
    int a;
    public Finalizer(int a)
    {
        this.a = a;
    }
    ~Finalizer()
    {
        Console.WriteLine("Object with finalizer destroyed 💀");
    }
}

class Disposed : IDisposable
{

    int n;
    public Disposed(int n)
    {
        this.n = n;
    }
    public void Dispose()
    {
        Console.WriteLine("Object with dispose");
    }
}
public class UsingDisposable : IDisposable
{
    public int numer;
    public UsingDisposable(int Numer)
    {
        numer = Numer;
        Console.WriteLine("Utworzono obiekt ");
    }
    public void Dispose()
    {
        Console.WriteLine("Zniszczono obiekt {0}");
    }
}

public class Program1
{
    public static void Main2(string[] args)
    {
        int objectNo = 10;
        Finalizer[] exampleFin = new Finalizer[objectNo];
        for (int i = 0; i < 10; i++)
            exampleFin[i] = new Finalizer(i);
        Thread.Sleep(5000);


        objectNo = 10;
        Disposed[] exampleDis = new Disposed[objectNo];
        for (int i = 0; i < 10; i++)
            exampleDis[i] = new Disposed(i);
        Thread.Sleep(5000);
        for (int i = 0; i < 10; i++)
            exampleDis[i].Dispose();

        using (UsingDisposable exampleUDis = new UsingDisposable(0))
        {
            Thread.Sleep(5000);
        }
    }
}