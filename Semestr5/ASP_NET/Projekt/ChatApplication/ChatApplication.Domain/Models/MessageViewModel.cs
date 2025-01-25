using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Models
{
    public class MessageViewModel
    {
        public string Content { get; set; }
        public string Sender { get; set; }
        public string Receiver { get; set; }
        public DateTime Date { get; set; }
    }
    
}
