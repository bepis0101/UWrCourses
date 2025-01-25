using System.ComponentModel.DataAnnotations;

namespace ChatApplication.Models
{
    public class AccountLoginModel : ErrorModel
    {
        [Required]
        public string Username { get; set; }
        [Required]
        public string Password { get; set; }

        public AccountLoginModel()
        {
            Errors = new List<string>();
        }
    }
}
