using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Person
{
    public string Name { get; set; }
    public string Surname { get; set; }
    public string PESEL { get; set; }
}

class Bank
{
    public string PESEL { get; set; }
    public string AccountNumber { get; set; }
}
public class Task5
{
    public static void Main5(string[] args)
    {
        //test data
        List<Person> people = new List<Person>
        {
            new Person { Name = "Jan", Surname = "Kowalski", PESEL = "12345678901" },
            new Person { Name = "Anna", Surname = "Nowak", PESEL = "12345678902" },
            new Person { Name = "Piotr", Surname = "Malinowski", PESEL = "12345678903" },
            new Person { Name = "Krzysztof", Surname = "Adamiak", PESEL = "12345678904" },
            new Person { Name = "Kamil", Surname = "Chaber", PESEL = "12345678905" },
            new Person { Name = "Tomasz", Surname = "Tarnowski", PESEL = "12345678906" }
        };
        List<Bank> banks = new List<Bank>
        {
            new Bank { PESEL = "12345678901", AccountNumber = "12345678901" },
            new Bank { PESEL = "12345678902", AccountNumber = "12345678902" },
            new Bank { PESEL = "12345678903", AccountNumber = "12345678903" },
            new Bank { PESEL = "12345678904", AccountNumber = "12345678904" },
            new Bank { PESEL = "12345678905", AccountNumber = "12345678905" },
            new Bank { PESEL = "12345678906", AccountNumber = "12345678906" }
        };
        var result = from person in people
                     join bank in banks on person.PESEL equals bank.PESEL
                     select new { person.Name, person.Surname, person.PESEL, bank.AccountNumber };
        foreach (var item in result)
        {
            Console.WriteLine(item);
        }
    }
}