using System.Xml.Linq;
public class XMLGenerator1
{
    public string GenerateXML(object dataObject)
    {
        XElement xElement = new("Data");
        foreach (var property in dataObject.GetType().GetProperties())
        {
            if (property.GetCustomAttributes(typeof(IgnoreInXML), true).Length > 0)
            {
                continue;
            }
            xElement.Add(new XElement(property.Name, property.GetValue(dataObject)));
        }
        return xElement.ToString();
    }
}

//define an attriute to ignore a property in XML generation
public class IgnoreInXML : System.Attribute
{
    public IgnoreInXML() { }
}
public class Person1
{
    public string Name { get; set; }
    [IgnoreInXML]
    public string Surname { get; set; }

}


public class Task3
{
    public static void Main3(string[] args)
    {
        Person1 person = new();
        person.Name = "John";
        person.Surname = "Doe";
        XMLGenerator1 xmlGenerator = new();
        string xml = xmlGenerator.GenerateXML(person);
        Console.WriteLine(xml);
    }   
}