using System.Collections;
using static ConsoleApp1.Zad3;

namespace ConsoleApp1
{
    public class Program
    {
        public static int IntComparer(int x, int y)
        {
            return x.CompareTo(y);
        }
        public static IComparer ComparerFromComparison(Comparison<int> cmp)
        {
            return new ComparisonAdapter(cmp);
        }
        public static void Main(string[] args)
        {

            var facade = new SmtpFacade();
            // Zapisz dane
            using (var fileToWrite = File.Create("example.dat"))
            using (var caeToWrite = new CaesarStream(fileToWrite, 5))
            {
                byte[] data = System.Text.Encoding.UTF8.GetBytes("Hello World!");
                caeToWrite.Write(data, 0, data.Length);
            }

            // Odczytaj dane
            using (var fileToRead = File.OpenRead("example.dat"))
            using (var caeToRead = new CaesarStream(fileToRead, -5))
            {
                byte[] buffer = new byte[1024];
                int bytesRead = caeToRead.Read(buffer, 0, buffer.Length);
                string result = System.Text.Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine(result); // powinno wypisać "Hello World!"
            }


            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };

            // Adapter: convert Comparison<int> to IComparer
            IComparer comparerAdapter = ComparerFromComparison(IntComparer);

            a.Sort(comparerAdapter);

            foreach (int i in a)
            {
                Console.Write(i + " ");
            }

            IService service = ServiceFactory.CreateService();

            try
            {
                string data = service.GetData(42);
                Console.WriteLine("Final result: " + data);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Final failure: " + ex.Message);
            }

            Console.ReadLine();

        }
    }
}
