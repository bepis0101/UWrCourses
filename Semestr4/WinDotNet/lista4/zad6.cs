using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class HTTPRequest
{
    public string Time { get; set; }
    public string IP { get; set; }
    public string Type { get; set; }
    public string URL { get; set; }
    public int Status { get; set; }
}
public class zad6
{
    public static void Main6(string[] args)
    {
        List<HTTPRequest> testData = GenerateTestData();
        
        var result = 
            from request in testData
            group request by request.IP into g
            select new
            {
                IP = g.Key,
                Requests = g.Count(),
            };
        result = result.OrderByDescending(x => x.Requests);
        foreach (var item in result)
        {
            Console.WriteLine(item.IP + " " + item.Requests);
        }
            
    }

    static List<HTTPRequest> GenerateTestData()
    {
        List<HTTPRequest> testData = new List<HTTPRequest>
        {
            new HTTPRequest { Time = "2024-03-17 08:00:00", IP = "192.168.1.1", Type = "GET", URL = "http://example.com/page1", Status = 200 },
            new HTTPRequest { Time = "2024-03-17 08:05:23", IP = "192.168.1.2", Type = "POST", URL = "http://example.com/page2", Status = 404 },
            new HTTPRequest { Time = "2024-03-17 08:10:45", IP = "192.168.1.3", Type = "GET", URL = "http://example.com/page3", Status = 500 },
            new HTTPRequest { Time = "2024-03-17 08:15:12", IP = "192.168.1.4", Type = "GET", URL = "http://example.com/page4", Status = 200 },
            new HTTPRequest { Time = "2024-03-17 08:20:30", IP = "192.168.1.1", Type = "POST", URL = "http://example.com/page5", Status = 200 },
            new HTTPRequest { Time = "2024-03-17 08:25:52", IP = "192.168.1.2", Type = "GET", URL = "http://example.com/page6", Status = 404 },
            new HTTPRequest { Time = "2024-03-17 08:30:17", IP = "192.168.1.3", Type = "POST", URL = "http://example.com/page7", Status = 200 },
            new HTTPRequest { Time = "2024-03-17 08:35:40", IP = "192.168.1.4", Type = "GET", URL = "http://example.com/page8", Status = 200 },
            new HTTPRequest { Time = "2024-03-17 08:40:59", IP = "192.168.1.1", Type = "GET", URL = "http://example.com/page9", Status = 500 },
            new HTTPRequest { Time = "2024-03-17 08:45:21", IP = "192.168.1.2", Type = "POST", URL = "http://example.com/page10", Status = 200 }
        };

        return testData;
    }
}