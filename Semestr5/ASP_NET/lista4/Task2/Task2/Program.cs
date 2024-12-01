using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Matching;

namespace Task2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            // Add services to the container.

            //builder.Services.AddControllers();
            builder.Services.AddSingleton<EndpointSelector, CustomEndpointSelector>();
            var app = builder.Build();

            // Configure the HTTP request pipeline.
            app.UseRouting();

            app.MapGet("/{param:string}", (string param) =>
            {
                return Results.Ok($"You requested param: {param}");
            });

            // parametr z ograniczeniem typu
            app.MapGet("/{id:int}", (int id) =>
            {
                return Results.Ok($"You requested id: {id} of type int");
            });
            // paramter z ograniczeniem dlugosci
            app.MapGet("/paramlen/{param:length(5, 10)}", (string param) =>
            {
                return Results.Ok($"You requested param: {param} of length 5-10");
            });
            // parametr z ograniczeniem wymagalnosci
            app.MapGet("/paramrequired/{param:required}", (string param) =>
            {
                return Results.Ok($"You requested param: {param} (param was required)");
            });
            // parametr z ograniczeniem regex
            app.MapGet("/regex/{param:regex(^[A-Z]*$)}", (string param) =>
            {
                return Results.Ok($"You requested param: {param} matching regex");
            });

            app.MapGet("conflict/{param:string}", (string param) =>
            {
                return Results.Ok($"You requested param: {param} of type string");
            });
            app.MapGet("conflict/{param:string:length(5, 10)}", (string param) =>
            {
                return Results.Ok($"You requested param: {param} of type string and length 5-10");
            });


            //app.UseEndpoints((endpoints) =>
            //{

            //});



            app.Run();
        }
    }
    class CustomEndpointSelector : EndpointSelector
    {
        public override async Task SelectAsync(HttpContext httpContext, CandidateSet candidateSet)
        {
            CandidateState cs = new CandidateState();
            for (int i = 0; i < candidateSet.Count; i++)
            {
                if (candidateSet.IsValidCandidate(i))
                {
                    cs = candidateSet[i];
                    break;
                }
            }
            httpContext.SetEndpoint(cs.Endpoint);
            httpContext.Request.RouteValues = cs.Values;
            await Task.CompletedTask;
        }
    }
}
