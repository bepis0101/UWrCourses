using Microsoft.Identity.Client;

namespace ChatApplication.Models
{
    public class Message
    {
        public Guid MessageId { get; set; }
        public string Content { get; set; }
        public DateTime TimeSent { get; set; }
        public Guid SenderId { get; set; }
        public Guid ReceiverId { get; set; }
        public User Sender { get; set; }
        public User Receiver { get; set; }
    }
}
