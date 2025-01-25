using System.ComponentModel.DataAnnotations;

namespace ChatApplication.Models
{
    public class MessageModel : ErrorModel
    {
        [Required]
        public string Content { get; set; }
        [Required]
        public string Sender { get; set; }
        [Required]
        public string Receiver { get; set; }
        [Required]
        public DateTime Date { get; set; }
    }
}
