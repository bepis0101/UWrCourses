using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class ListHelper
{
    public static List<TOutput> ConvertAll<T, TOutput>(List<T> list, Converter<T, TOutput> converter)
    {

    }
    public static List<T> FindAll<T>(
    List<T> list,
    Predicate<T> match);
    public static void ForEach<T>(List<T>, Action<T> action);
    public static int RemoveAll<T>(
    List<T> list,
    Predicate<T> match);
    public static void Sort<T>(
    List<T> list,
    Comparison<T> comparison);
}

public class Program5
{

    public static void Main5(string[] args)
    {

    }
}