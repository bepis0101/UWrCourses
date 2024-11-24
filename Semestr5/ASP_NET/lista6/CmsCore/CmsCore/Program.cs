using Microsoft.AspNetCore.Mvc;
namespace CmsCore
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var services = builder.Services;
            services.AddControllersWithViews();
            services.AddSingleton<CmsRoute>();

            var app = builder.Build();
            app.UseRouting();

            app.MapDynamicControllerRoute<CmsRoute>(
                "CMS/{**sitepage}"
            );
            app.MapControllerRoute(
                name: "default",
                pattern: "{controller=Home}/{action=Index}/{id?}"
            );

            app.MapGet("/", () => "Hello World!");

            app.Run();
        }
    }
}
