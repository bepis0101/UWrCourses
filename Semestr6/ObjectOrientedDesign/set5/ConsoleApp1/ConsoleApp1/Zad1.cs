using System.Net.Mail;
using System.Net;
namespace ConsoleApp1
{
    public class SmtpFacade
    {
        public void Send(string from, string to, string subject, string body,
                            Stream attachment, string attachmentMimeType)
        {
            using (var message = new MailMessage())
            {
                message.From = new MailAddress(from);
                message.To.Add(new MailAddress(to));
                message.Subject = subject;
                message.Body = body;

                if (attachment != null && attachmentMimeType != null)
                {
                    // Generujemy unikalną nazwę pliku
                    string fileName = "attachment" + GetExtensionFromMimeType(attachmentMimeType);
                    var mailAttachment = new Attachment(attachment, fileName, attachmentMimeType);
                    message.Attachments.Add(mailAttachment);
                }

                using (var smtpClient = new SmtpClient())
                {
                    // Konfiguracja klienta SMTP — można dostosować do środowiska
                    smtpClient.Host = "smtp.example.com"; // <-- ustaw właściwy adres serwera SMTP
                    smtpClient.Port = 587;                // <-- ustaw port (np. 587 dla STARTTLS)
                    smtpClient.EnableSsl = true;
                    smtpClient.Credentials = new NetworkCredential("your-username", "your-password"); // <-- dane logowania

                    smtpClient.Send(message);
                }
            }
        }

        // Pomocnicza metoda do określania rozszerzenia z typu MIME (opcjonalne)
        private string GetExtensionFromMimeType(string mimeType)
        {
            switch (mimeType)
            {
                case "application/pdf": return ".pdf";
                case "image/jpeg": return ".jpg";
                case "image/png": return ".png";
                case "text/plain": return ".txt";
                default: return "";
            }
        }
    }

}
