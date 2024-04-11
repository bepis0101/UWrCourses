using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq.Expressions;

public class DynamicPerson : DynamicObject
{
    private Dictionary<string, object> properties = new Dictionary<string, object>();

    public override bool TryGetMember(GetMemberBinder binder, out object result)
    {
        string propertyName = binder.Name;
        return properties.TryGetValue(propertyName, out result);
    }

    // Metoda wywoływana, gdy ustawiamy wartość za pomocą składni kropki, np. obj.LastName = "Doe"
    public override bool TrySetMember(SetMemberBinder binder, object value)
    {
        string propertyName = binder.Name;
        properties[propertyName] = value;
        return true;
    }

    // Metoda wywoływana, gdy odczytujemy wartość za pomocą indeksu, np. obj["Age"]
    public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
    {
        string key = indexes[0] as string;
        if (key != null)
        {
            return properties.TryGetValue(key, out result);
        }
        else
        {
            result = null;
            return false;
        }
    }

    // Metoda wywoływana, gdy ustawiamy wartość za pomocą indeksu, np. obj["Age"] = 30
    public override bool TrySetIndex(SetIndexBinder binder, object[] indexes, object value)
    {
        string key = indexes[0] as string;
        if (key != null)
        {
            properties[key] = value;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Metoda wywoływana, gdy wywołujemy obiekt jak metodę, np. obj.PrintDetails()
    public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
    {
        if (binder.Name == "PrintDetails")
        {
            result = $"Imię: {properties["FirstName"]}, Nazwisko: {properties["LastName"]}, Wiek: {properties["Age"]}";
            return true;
        }
        else
        {
            result = null;
            return false;
        }
    }

    public override bool TryUnaryOperation(UnaryOperationBinder binder, out object result)
    {
        if (binder.Operation == ExpressionType.Negate && properties.ContainsKey("Age"))
        {
            result = -(int)properties["Age"];
            return true;
        }
        else
        {
            result = null;
            return false;
        }
    }

    // Metoda wywoływana, gdy wykonujemy operację binarną na obiekcie, np. obj1 + obj2
    public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
    {
        if (binder.Operation == ExpressionType.Add && properties.ContainsKey("Age") && arg is int)
        {
            result = (int)properties["Age"] + (int)arg;
            return true;
        }
        else
        {
            result = null;
            return false;
        }
    }
}


public class Task2
{
    static void Main2(string[] args)
    {
        dynamic person = new DynamicPerson();

        // Ustawianie wartości za pomocą składni kropki
        person.FirstName = "John";
        person.LastName = "Doe";
        person.Age = 30;

        // Odczytanie wartości za pomocą składni kropki
        Console.WriteLine(person.FirstName); // John
        Console.WriteLine(person.Age); // 30

        // Ustawianie wartości za pomocą indeksu
        person["Occupation"] = "Developer";

        // Odczytanie wartości za pomocą indeksu
        Console.WriteLine(person["Occupation"]); // Developer

        // Wywołanie metody dynamicznie
        Console.WriteLine(person.PrintDetails()); // Imię: John, Nazwisko: Doe, Wiek: 30

        Console.WriteLine(-person.Age); // -30

        // Wykonanie operacji binarnej dodawania wieku
        Console.WriteLine(person.Age + 10); // 40
    }
}
