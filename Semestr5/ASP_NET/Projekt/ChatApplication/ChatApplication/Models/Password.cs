namespace ChatApplication.Models
{
    public class Password
    {
        public Guid Id { get; set; }
        public string PasswordHash { get; set; }
        public Guid UserId { get; set; }
    }
}
