/*
Borys Adamiak
Lista 3 Programowanie Obiektowe
Zadanie 4
*/
using System;


public class Vector
{
    int size;
    float[] coords;
    public Vector(int size)
    {
        this.size = size;
        coords = new float[size];
        for(int i = 0; i < size; i++)
        {
            coords[i] = 0;
        }
    }
    public int size_()
    {
        return this.size;
    }
    public float[] tab()
    {
        return coords;
    }

    public void set_vector(float[] tab)
    {
        if(tab.Length != size) return;
        else
        {
            for(int i = 0; i < size; i++)
            {
                coords[i] = tab[i];
            }
        }
    }

    public static Vector operator+ (Vector V, Vector C)
    {
        Vector res = new Vector(V.size);
        float[] result = new float[V.size];
        if(V.size == C.size)
        {
            for(int i = 0; i < C.size; i++)
            {
                result[i] = C.coords[i] + V.coords[i];
            }
        }
        res.set_vector(result);
        return res;
    }

    public static Vector operator* (Vector V, float S)
    {
        Vector res = new Vector(V.size);
        float[] result = new float[V.size];
        for(int i = 0; i < V.size; i++)
        {
            result[i] = V.coords[i]*S;
        }
        res.set_vector(result);
        return res;
    }


    public static float operator*(Vector V, Vector X)
    {
        float res = 0f;
        if(V.size == X.size)
        {
            for(int i = 0; i < V.size; i++)
            {
                res += V.coords[i]*X.coords[i];
            }
        }
        return res;
    }
    
    public float norma()
    {
        return (float)Math.Sqrt(this*this);
    }
    public void print()
    {
        for(int i = 0; i < size; i++)
        {
            Console.Write(coords[i]);
            Console.Write(' ');
        }
        Console.Write('\n');
    }
}
