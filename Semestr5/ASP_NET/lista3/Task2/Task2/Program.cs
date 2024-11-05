using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Routing;


namespace Task2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            builder.Services.AddControllers();
            var app = builder.Build();

            app.MapGet("/", (HttpContext context) =>
            {
                return Results.Ok("Hello, World!");
            });

            app.MapControllers();
            app.Run();
        }
    }
}
