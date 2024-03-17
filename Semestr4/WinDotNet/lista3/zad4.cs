using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Security.Cryptography;




public class Program4
{

    public static void Main4(string[] args)
    {
        List<int> nums = new() { 1, 3, 4, 9, 12, 1, 10 };
        nums = nums.ConvertAll(delegate (int i) { return i * i; });
        nums.ForEach(delegate (int i) { Console.Write(i); Console.Write(' '); });
        Console.Write('\n');
        nums.RemoveAll(delegate (int i) { return i % 2 == 0; });
        nums.ForEach(delegate (int i) { Console.Write(i); Console.Write(' '); });
        nums.Sort(delegate(int a, int b) 
        {
            return a < b ? 1 : -1;
        });
        Console.Write('\n');
        nums.ForEach(delegate (int i) { Console.Write(i); Console.Write(' '); });
    }
}