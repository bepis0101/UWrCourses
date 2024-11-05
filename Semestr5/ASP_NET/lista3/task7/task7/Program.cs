using System.Text;

namespace task7
{
    public class Program
    {
        private static int calcSignature(string filename, long fileSize)
        {
            int signature = 0;
            foreach (char c in filename)
            {
                signature += c;
            }
            signature += (int)fileSize;
            return signature % 0xFFFF;
        }
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            var app = builder.Build();
            app.UseStaticFiles();
            app.UseRouting();

            app.MapGet("/", (HttpContext context) =>
            {
                context.Response.ContentType = "text/html";
                return context.Response.SendFileAsync("./index.html");
            });
            app.MapPost("/upload", async (HttpContext context) =>
            {
                var file = context.Request.Form.Files["file"];
                if (file != null)
                {
                    string filename = file.FileName;
                    var fileSize = file.Length;
                    int signature = calcSignature(filename, fileSize);

                    string xml = $@"
    <opis>
        <filename>{filename}</filename>
        <filesize>{fileSize}</filesize>
        <signature>{signature}</signature>
    </opis>";
                    context.Response.Clear();
                    context.Response.ContentType = "text/xml";
                    context.Response.Headers.Add("Content-Disposition", "attachment; filename=opis.xml");
                    byte[] xmlBytes = Encoding.UTF8.GetBytes(xml); 
                    await context.Response.Body.WriteAsync(xmlBytes, 0, xmlBytes.Length);
                    return;
                }
                else
                {
                    await context.Response.WriteAsync("No file uploaded");
                }
            });

            app.Run();
        }
    }
}
