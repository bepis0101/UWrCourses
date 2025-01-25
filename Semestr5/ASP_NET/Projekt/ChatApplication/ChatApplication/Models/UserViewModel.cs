namespace ChatApplication.Models
{
    public class UserViewModel : ErrorModel
    {
        public Guid Id { get; set; }
        public string Username { get; set; }
        public string Email { get; set; }
    }
}
