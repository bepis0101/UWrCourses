using Microsoft.AspNetCore.Hosting.Server;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Security.Cryptography;
using System;

namespace httphandler
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var app = builder.Build();

            app.Map("/{**catchAll}", async (HttpContext context) => {
                var url = $"{context.Request.Scheme}://{context.Request.Host}{context.Request.PathBase}{context.Request.Path}{context.Request.QueryString}";
                var headers = context.Request.Headers.Select(h => $"{h.Key}: {h.Value}");
                var method = context.Request.Method;
                var body = await new StreamReader(context.Request.Body).ReadToEndAsync();
                var response = $"URL: {url}\nMethod: {method}\nHeaders:\n\t{string.Join("\n\t", headers)}\nBody:\n{body}";
                await context.Response.WriteAsync(response);
            });

//              Hyperlink to klasyczne przekierowanie po stronie klienta,
//              gdzie przegl�darka wysy�a nowe ��danie GET.

//              POST mi�dzy stronami przekierowuje dane przez formularz POST
//              i jest wykorzystywane g��wnie do przesy�ania danych ukrytych.

//              Response.Redirect wykonuje pe�ne przekierowanie po stronie serwera
//              z informacj� dla przegl�darki(zmienia si� URL i przegl�darka wysy�a nowe ��danie).

//              Server.Transfer dzia�a na serwerze bez informowania przegl�darki
//              o przekierowaniu(URL w przegl�darce si� nie zmienia).


            app.Run();
        }
    }
}
