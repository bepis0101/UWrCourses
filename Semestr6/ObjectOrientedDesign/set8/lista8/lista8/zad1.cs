using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista8
{
    public class Message(string title, string content)
    {
        public string Title { get; set; } = title;
        public string Content { get; set; } = content;
    }

    public class Request(Message message)
    {
        public Message Message { get; set; } = message;
        public string? MessageType { get; set; } = null;
    }
    public abstract class Handler
    {
        protected Handler next;

        public Handler SetNext(Handler handler)
        {
            next = handler;
            return handler;
        }

        public void Handle(Request request)
        {
            Process(request);
            next?.Handle(request);
        }

        protected abstract void Process(Request request);
    }
    public class ClassifierHandler : Handler
    {
        protected override void Process(Request request)
        {
            var title = request.Message.Title;
            var content = request.Message.Content?.ToLower();

            if (string.IsNullOrWhiteSpace(title) || string.IsNullOrWhiteSpace(content))
            {
                request.MessageType = "invalid";
            }
            else if (content.Length > 1000)
            {
                request.MessageType = "invalid";
            }
            else if (content.Contains("dzięk", StringComparison.CurrentCultureIgnoreCase))
            {
                request.MessageType = "praise";
            }
            else if (content.Contains("skarg", StringComparison.CurrentCultureIgnoreCase) || 
                     content.Contains("reklamacj", StringComparison.CurrentCultureIgnoreCase))
            {
                request.MessageType = "complaint";
            }
            else if (content.Contains("zamów", StringComparison.CurrentCultureIgnoreCase))
            {
                request.MessageType = "order";
            }
            else
            {
                request.MessageType = "other";
            }
        }
    }
    public class PraiseHandler : Handler
    {
        protected override void Process(Request request)
        {
            if (request.MessageType == "praise")
            {
                Console.WriteLine("Obsługa pochwały: " + request.Message.Title);
            }
        }
    }

    public class ComplaintHandler : Handler
    {
        protected override void Process(Request request)
        {
            if (request.MessageType == "complaint")
            {
                Console.WriteLine("Obsługa skargi: " + request.Message.Title);
            }
        }
    }

    public class OrderHandler : Handler
    {
        protected override void Process(Request request)
        {
            if (request.MessageType == "order")
            {
                Console.WriteLine("Obsługa zamówienia: " + request.Message.Title);
            }
        }
    }

    public class OtherHandler : Handler
    {
        protected override void Process(Request request)
        {
            if (request.MessageType == "other")
            {
                Console.WriteLine("Obsługa innej wiadomości: " + request.Message.Title);
            }
        }
    }

    public class InvalidMessageHandler : Handler
    {
        protected override void Process(Request request)
        {
            if (request.MessageType == "invalid")
            {
                Console.WriteLine("Nieprawidłowa wiadomość: " + request.Message.Title);
            }
        }
    }

    public class ArchiveHandler : Handler
    {
        protected override void Process(Request request)
        {
            var path = Guid.NewGuid().ToString();
            File
                .CreateText(path)
                .Write(request.Message.Title + "\n" + request.Message.Content);
                
            Console.WriteLine("Archiwizuję wiadomość: " + 
                              request.Message.Title     + 
                              "i zapisuje do pliku "    + 
                              path                      + 
                              ".txt");
        }
    }

}
