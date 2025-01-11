using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Models
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
