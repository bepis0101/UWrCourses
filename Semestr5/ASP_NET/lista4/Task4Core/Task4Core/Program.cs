using Microsoft.Extensions.Options;

namespace Task4Core
{
    class AppSettings
    {
        public string AppTitle { get; set; }
        public string AppVersion { get; set; }
    }
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            builder.Configuration.AddJsonFile("Configuration/jsconfig.json", optional: true, reloadOnChange: true);
            builder.Configuration.AddXmlFile("Configuration/web.config", optional: true, reloadOnChange: true);
            builder.Services.Configure<AppSettings>(builder.Configuration.GetSection("AppSettings"));
            var app = builder.Build();

            var config = app.Configuration;
            var titleJson = config["AppSettings:AppTitle"];
            var versionJson = config["AppSettings:AppVersion"];
            var titleXml = config["AppTitle"];
            var versionXml = config["AppVersion"];

            var appSettings = app.Services.GetRequiredService<IOptions<AppSettings>>().Value;

            app.MapGet("/", () =>
            {
                Results.Ok($"Title Json: {titleJson}\n" +
                    $"Title XML: {titleXml}\n" +
                    $"Version JSON: {versionJson}"
                    );
            });

            app.Run();
        }
    }
}
