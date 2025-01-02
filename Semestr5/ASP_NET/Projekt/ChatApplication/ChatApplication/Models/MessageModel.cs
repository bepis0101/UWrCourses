using System.ComponentModel.DataAnnotations;

namespace ChatApplication.Models
{
    public class MessageModel
    {
        [Required]
        public string Content { get; set; }
        [Required]
        public string Sender { get; set; }
        [Required]
        public string Receiver { get; set; }
    }
}
