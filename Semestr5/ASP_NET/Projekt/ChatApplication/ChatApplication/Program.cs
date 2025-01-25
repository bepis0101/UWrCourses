using ChatApplication.Domain;
using ChatApplication.Domain.Handler;
using ChatApplication.Domain.Handlers;
using ChatApplication.Hubs;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.EntityFrameworkCore;

namespace ChatApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            // Add services to the container.
            builder.Services.AddControllersWithViews();
            builder.Services.AddSignalR();
            builder.Services
                .AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
                .AddCookie(options =>
                {
                    options.LoginPath = "/Account/Login";
                    options.SlidingExpiration = true;
                });

            builder.Services.AddDbContext<DbManager>(options =>
                options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));

            builder.Services.AddMediatR(config =>
            {
                config.RegisterServicesFromAssemblies(
                    typeof(ChatHandler).Assembly,
                    typeof(LoginHandler).Assembly,
                    typeof(MessageHandler).Assembly,
                    typeof(MessageSenderHandler).Assembly,
                    typeof(SignUpHandler).Assembly,
                    typeof(UserHandler).Assembly
                );
            });

            var app = builder.Build();

            // Configure the HTTP request pipeline.
            if (!app.Environment.IsDevelopment())
            {
                app.UseExceptionHandler("/Home/Error");
            }
            app.UseStaticFiles();

            app.MapHub<ChatHub>("/chatHub");

            app.UseRouting();

            app.UseAuthentication();

            app.UseAuthorization();

            app.MapControllerRoute(
                name: "default",
                pattern: "{controller=Home}/{action=Index}/{id?}");

            app.Run();
        }
    }
}
