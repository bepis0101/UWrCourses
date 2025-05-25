using lista9_2.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Sqlite;
using SQLitePCL;
namespace lista9_2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Batteries.Init();
            using var context = new DataAccess();
            context.Database.EnsureCreated();
            // Dodanie danych
            var parent = new Parent { Name = "Anna" };
            parent.Children.Add(new Child { Name = "Zosia" });
            parent.Children.Add(new Child { Name = "Janek" });

            context.Parents.Add(parent);
            context.SaveChanges();

            // Pobranie i wyświetlenie danych
            var parents = context.Parents
                .Include(p => p.Children)
                .ToList();

            foreach (var p in parents)
            {
                Console.WriteLine($"Rodzic: {p.Name}");
                foreach (var c in p.Children)
                {
                    Console.WriteLine($"  Dziecko: {c.Name}");
                }
            }
        }
    }
}
