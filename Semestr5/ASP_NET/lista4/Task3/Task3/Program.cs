namespace Task3
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            builder.Services.AddScoped<IDapperRepository, DapperRepository>();
            var app = builder.Build();

            app.MapGet("/", async(IDapperRepository repo) =>
            {
                var data = await repo.GetAllAsync();
                return Results.Ok(data);
            });

            app.Run();
        }
    }
}
