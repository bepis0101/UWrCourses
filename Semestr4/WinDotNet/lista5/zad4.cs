using Microsoft.Diagnostics.Tracing.Parsers.MicrosoftAntimalwareEngine;
using System.Runtime.CompilerServices;

internal static class TaskExtensionA
{
    public static HttpClient HttpClient { get; } = new HttpClient();
    
    public static async Task<string> GetContent(string url)
    {
        var res = await HttpClient.GetAsync(url);
        res.EnsureSuccessStatusCode();

        return await res.Content.ReadAsStringAsync();
    }
    public static TaskAwaiter<string> GetAwaiter(this string url)
    {
        return GetContent(url).GetAwaiter();
    }
}

public class Task4
{
    public static async Task Main4(string[] args)
    {
        Console.WriteLine(await "https://ii.uni.wroc.pl/");
    }
}