using BC = BCrypt.Net.BCrypt;
using System.Dynamic;

namespace ChatApplication.Services
{
    public static class PasswordHandler
    {
        private const int Iterations = 12;

        public static string HashPassword(string password)
        {
            return BC.HashPassword(password, Iterations);
        }

        public static bool VerifyPassword(string password, string hash)
        {
            return BC.Verify(password, hash);
        }
    }
}
