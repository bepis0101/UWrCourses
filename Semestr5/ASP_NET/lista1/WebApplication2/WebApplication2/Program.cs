namespace WebApplication2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var app = builder.Build();

            app.MapGet("/", () =>
            {
                const string PATH = "C:\\Users\\borys\\Downloads\\a.txt";
                try
                {
                    using (var stream = new StreamReader(PATH))
                    {
                        return stream.ReadToEnd();
                    }
                }
                catch (Exception e)
                {
                    return e.Message;
                }
            });

            app.Run();
        }
    }
}
