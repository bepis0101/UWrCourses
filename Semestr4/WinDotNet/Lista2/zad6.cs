using System;
using System;

public class Vector2D
{
    public double X { get; }
    public double Y { get; }

    public Vector2D(double x, double y)
    {
        X = x;
        Y = y;
    }

    public static Vector2D operator +(Vector2D v1, Vector2D v2)
    {
        return new Vector2D(v1.X + v2.X, v1.Y + v2.Y);
    }

    public static Vector2D operator -(Vector2D v1, Vector2D v2)
    {
        return new Vector2D(v1.X - v2.X, v1.Y - v2.Y);
    }

    public override string ToString()
    {
        return $"({X}, {Y})";
    }
}

class Program6
{
    static void Main6()
    {
        Vector2D v1 = new (1, 2);
        Vector2D v2 = new (3, 4);

        // Dodawanie wektorów
        Vector2D v3 = v1 + v2;
        Console.WriteLine("Dodawanie wektorów: " + v3);  // Output: (4, 6)

        // Odejmowanie wektorów
        Vector2D v4 = v1 - v2;
        Console.WriteLine("Odejmowanie wektorów: " + v4);  // Output: (-2, -2)
    }
}
