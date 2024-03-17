using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Task4 
{
    public static void Main4(string[] args)
    {
        string folderPath = "C:\\Users\\borys\\Desktop\\UWr\\Semestr4\\WinDotNet\\lista4";
        if(Directory.Exists(folderPath))
        {
            var files = Directory.GetFiles(folderPath);
            var totalSize =
                from file in files
                select new FileInfo(file).Length;
            Console.WriteLine(totalSize.Aggregate((x, y) => x + y));
        }
        else
        {
            Console.WriteLine("Folder does not exist");
        }
    }
}
