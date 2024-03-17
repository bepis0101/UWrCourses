using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Task7
{
    public static void Main7(string[] args)
    {
        var item = new { Name = "Maciek", Age = 10 };
        var item2 = new { Name = "Maciej", Age = 25 };
        List<object> list = new List<object>() { item, item2 };
        foreach (var i in list)
        {
            Console.WriteLine(i);
        }
    }

}