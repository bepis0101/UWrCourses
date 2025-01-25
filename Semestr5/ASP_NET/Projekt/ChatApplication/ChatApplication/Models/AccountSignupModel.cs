using System.ComponentModel.DataAnnotations;

namespace ChatApplication.Models
{
    public class AccountSignupModel : ErrorModel
    {
        [Required]
        public string Email { get; set; }
        [Required]
        public string Username { get; set; }
        [Required]
        public string Password { get; set; }
        [Required]
        public string ConfirmPassword { get; set; }

        public AccountSignupModel()
        {
            Errors = new List<string>();
        }
    }
}
