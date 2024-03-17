using System.Xml.Linq;

public class XMLGeneratorChilled
{
    public string GenerateXML(object dataObject)
    {
        XElement xElement = new("Data");
        foreach (var property in dataObject.GetType().GetProperties())
        {
            xElement.Add(new XElement(property.Name, property.GetValue(dataObject)));
        }
        return xElement.ToString();
    }
}


public class PersonChilled
{
    public string Name { get; set; }
    public string Surname { get; set; }
    
}


public class Task2
{
    public static void Main2(string[] args)
    {
        Person person = new Person();
        person.Name = "John";
        person.Surname = "Doe";
        XMLGenerator xmlGenerator = new();
        string xml = xmlGenerator.GenerateXML(person);
        Console.WriteLine(xml);
    }
}
