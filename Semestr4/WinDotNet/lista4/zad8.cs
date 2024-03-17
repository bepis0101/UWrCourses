using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Task8
{
    public static void Main(string[] args)
    {
        Func<int, int> recursion = null;
        recursion = (int i) =>
        {
            if (i > 2)
            {
                return recursion(i - 1) + recursion(i - 2);
            }
            else
            {
                return 1;
            }
        };

        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine(recursion(i));
        }
    }
}
