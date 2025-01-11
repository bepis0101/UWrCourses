﻿using BC = BCrypt.Net.BCrypt;

namespace ChatApplication.Domain.Services
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
