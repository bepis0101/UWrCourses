using System;
using System.Diagnostics;

public class Person
{

    private string _name; 
    private string _surname;
    public string Name
    {
        get => _name;
        set
        {
            if(_name != value)
            {
                OnFieldChanged("Name", _name, value);
                _name = value;
            }
        }
    }
    public string Surname
    {
        get => _surname;
        set
        {
            if (_surname != value)
            {
                OnFieldChanged("Surname", _surname, value);
                _surname = value;
            }
        }
    }
    public Person()
    {
        this.Name = "";
        this.Surname = "";
    }
    public static event EventHandler<FieldChangedEventArgs> FieldChanged;

    protected virtual void OnFieldChanged(string fieldName, string oldVal, string newVal)
    {
        FieldChanged?.Invoke(this, new FieldChangedEventArgs(fieldName, oldVal, newVal));
    }
}
public class FieldChangedEventArgs : EventArgs
{
    public string fieldName { get; }
    public object oldVal { get; }
    public object newVal { get; }

    public FieldChangedEventArgs(string fieldName, object oldVal, object newVal)
    {
        this.fieldName = fieldName;
        this.oldVal = oldVal;
        this.newVal = newVal;
    }
}


class Program4
{
    public static void Main(string[] args)
    {
        Person p = new();
        Person.FieldChanged += (sender, args) =>
        {
            Console.WriteLine($"arg {args.fieldName} old: {args.oldVal} new:{args.newVal}");
        };
        p.Name = "John";
        p.Surname = "Doe";
    }
}