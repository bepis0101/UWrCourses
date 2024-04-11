using Microsoft.Diagnostics.Tracing.Parsers.Kernel;
using System.Runtime.CompilerServices;

internal static class TaskExtensions
{
    public static TaskAwaiter GetAwaiter(this int miliseconds)
    {
        return Task.Delay(miliseconds).GetAwaiter();
    }


}
public class Task3
{
    public static async Task Main3(string[] args)
    {
        Console.WriteLine("Task 3");
        await 2000;
        Console.WriteLine("Task 3");
    }
}