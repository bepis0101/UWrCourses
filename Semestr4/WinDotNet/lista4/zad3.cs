using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Task3
{
    public static void Main3(string[] args)
    {
        List<string> names = new List<string> { "Malinowski", "Adamiak", "Chaber", "Tarnowski" };
        IEnumerable<char> namesFirstLetter =
            (from name in names
            group name[0] by name[0] into g
            orderby g.Key
            select g.Key);
        foreach (var letter in namesFirstLetter)
        {
            Console.WriteLine(letter);
        }
    }

}