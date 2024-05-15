using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Net.Mail;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace lista9
{
    internal class Task3
    {
        static void Main(string[] args)
        {
            var tasks = new List<Task>
            {
                UseHTTPClient(),
                UseSMTPClient(),
                UseTCPClient()
            };

            Task.WaitAll(tasks.ToArray());
        }

        static async Task UseHTTPClient()
        {
            using(var client = new HttpClient())
            {
                try
                {
                    var response = await client.GetAsync("https://ii.uni.wroc.pl/");
                    response.EnsureSuccessStatusCode();
                    string res = await response.Content.ReadAsStringAsync();
                    Console.WriteLine(res);
                }
                catch (HttpRequestException e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        static async Task UseSMTPClient()
        {
            using(var client = new SmtpClient("smtp.gmail.com"))
            {
                client.Port = 587;
                client.Credentials = new NetworkCredential("your-email@gmail.com", "your-password");
                client.EnableSsl = true;
                var message = new MailMessage("your-email@gmail.com", "recipient@example.com", "Test Subject", "Test Body");
                try
                {
                    await client.SendMailAsync(message);
                    Console.WriteLine("Mail sent");
                }
                catch (SmtpException e)
                {
                    Console.WriteLine(e.Message);
                }
                finally
                {
                    message.Dispose();
                }
            }
        }

        static async Task UseTCPClient()
        {
            using(var client = new TcpClient())
            {
                try
                {
                    await client.ConnectAsync("google.com", 80);
                    Console.WriteLine("Connected to google.com");
                }
                catch (SocketException e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }
    }
}
