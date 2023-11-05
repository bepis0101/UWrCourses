/*
Borys Adamiak
Lista 3 Programowanie Obiektowe
Zadanie 4
mcs -reference:wektor-lib.dll wektor.cs
./wektor.exe
*/
using System;


class Program
{
    public static void Main()
    {
        Vector V = new Vector(3);
        float[] tab = {3.2f, 2.4f, 4.5f};
        V.set_vector(tab);
        V = V*4;
        V.print();
        Vector X = new Vector(3);
        float[] tab2 = {5.7f, 2f, 3f};
        X.set_vector(tab2);
        X.print();
        V = V + X;
        V.print();
        Console.WriteLine(V*X);
        Console.WriteLine(V.norma());
    }
}