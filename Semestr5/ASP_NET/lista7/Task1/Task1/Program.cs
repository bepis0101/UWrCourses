namespace Task1
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            builder.Services.AddAuthentication("Windows");
            builder.Services.AddAuthorization();
            var app = builder.Build();

            app.UseAuthentication();
            app.UseAuthorization();

            app.MapGet("/", (HttpContext context) =>
            {
                var user = context.User;
                return context.Response.WriteAsync($"<h1>Hello, {user.Identity?.Name}, {user.Identity?.IsAuthenticated}, {user.Identity?.AuthenticationType}</h1>");
            });

            app.Run();
        }
    }
}
