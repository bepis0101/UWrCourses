using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista3
{
    public class DataProvider
    {
        public string GetData()
        {
            return "some data";
        }
    }

    public class ReportFormatter
    {
        public string FormatData(string data)
        {
            return $"Formatted data {data}";
        }
    }

    public class ReportProvider
    {
        private readonly DataProvider _data;
        private readonly ReportFormatter _formatter;
        public ReportProvider(DataProvider data, ReportFormatter formatter)
        {
            _data = data;
            _formatter = formatter;
        }

        public void Print()
        {
            var data = _data.GetData();
            var formatted = _formatter.FormatData(data);
            Console.WriteLine(formatted);
        }
    }

    public class Zad2
    {
        static void Main2(string[] args)
        {
            var data = new DataProvider();
            var formater = new ReportFormatter();
            var report = new ReportProvider(data, formater);
            report.Print();
        }
    }
}
