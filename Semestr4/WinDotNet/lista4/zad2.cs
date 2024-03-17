using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Dany jest plik tekstowy zawierający zbiór liczb naturalnych w kolejnych liniach.
//Napisać wyrażenie LINQ, które odczyta kolejne liczby z pliku i wypisze tylko liczby większe
//niż 100, posortowane malejąco.

public class Task2
{
    public static void Main2(string[] args)
    {
        string[] lines = File.ReadAllLines("C:\\Users\\borys\\Desktop\\UWr\\Semestr4\\WinDotNet\\lista4\\numbers.txt");
        var numbers = lines.Select(x => int.Parse(x)).Where(x => x > 100).OrderByDescending(x => x);
        foreach (var number in numbers)
        {
            Console.WriteLine(number);
        }
    }
}