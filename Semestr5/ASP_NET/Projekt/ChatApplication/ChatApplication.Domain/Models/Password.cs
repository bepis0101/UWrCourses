using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Models
{
    public class Password
    {
        public Guid Id { get; set; }
        public string PasswordHash { get; set; }
        public Guid UserId { get; set; }
    }
}
