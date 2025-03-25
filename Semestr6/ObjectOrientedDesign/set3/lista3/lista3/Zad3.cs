using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace lista3
{
    public class Item
    {
        public string Name { get; set; }
        public decimal Price { get; set; }
    }
    public interface ITaxCalculator
    {
        decimal CalculateTax(decimal price);
    }

    public class StandardTaxCalculator : ITaxCalculator
    {
        public decimal CalculateTax(decimal price) => price * 0.22m;
    }

    public class ReducedTaxCalculator : ITaxCalculator
    {
        public decimal CalculateTax(decimal price) => price * 0.10m;
    }
    

    public interface IBillPrinter
    {
        void PrintBill(Item[] items, ITaxCalculator taxCalculator);
    }

    public class AlphabeticalBillPrinter : IBillPrinter
    {
        public void PrintBill(Item[] items, ITaxCalculator taxCalculator)
        {
            var sortedItems = items.OrderBy(i => i.Name);
            foreach (var item in sortedItems)
            {
                Console.WriteLine("Towar {0} : cena {1} + podatek {2}",
                    item.Name, item.Price, taxCalculator.CalculateTax(item.Price));
            }
        }
    }

    public class PriceDescendingBillPrinter : IBillPrinter
    {
        public void PrintBill(Item[] items, ITaxCalculator taxCalculator)
        {
            var sortedItems = items.OrderByDescending(i => i.Price);
            foreach (var item in sortedItems)
            {
                Console.WriteLine("Towar {0} : cena {1} + podatek {2}",
                    item.Name, item.Price, taxCalculator.CalculateTax(item.Price));
            }
        }
    }
    public class CashRegister
    {
        private readonly ITaxCalculator _taxCalculator;
        private readonly IBillPrinter _billPrinter;

        public CashRegister(ITaxCalculator taxCalculator, IBillPrinter billPrinter)
        {
            _taxCalculator = taxCalculator;
            _billPrinter = billPrinter;
        }

        public decimal CalculatePrice(Item[] items)
        {
            decimal totalPrice = 0;
            foreach (var item in items)
            {
                totalPrice += item.Price + _taxCalculator.CalculateTax(item.Price);
            }
            return totalPrice;
        }

        public void PrintBill(Item[] items)
        {
            _billPrinter.PrintBill(items, _taxCalculator);
        }
    }
    



    class Zad3
    {
        public static void Main3(string[] args)
        {
            var items = new[]
        {
            new Item { Name = "Laptop", Price = 3000 },
            new Item { Name = "Monitor", Price = 1200 },
            new Item { Name = "Mouse", Price = 100 }
        };

            var taxCalculator = new StandardTaxCalculator(); // Możemy łatwo podmienić strategię
            var billPrinter = new AlphabeticalBillPrinter(); // Możemy łatwo podmienić strategię

            var cashRegister = new CashRegister(taxCalculator, billPrinter);
            decimal totalPrice = cashRegister.CalculatePrice(items);
            Console.WriteLine("Total price: " + totalPrice);

            cashRegister.PrintBill(items);
        }
    }
}
