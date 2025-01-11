using ChatApplication.Domain.Models;
using ChatApplication.Domain.Services;
using MediatR;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Handlers
{
    public class SignUpUseCaseParameters : IRequest<SignUpUseCaseResult>
    {
        public string Username { get; set; }
        public string Password { get; set; }
        public string Email { get; set; }
        public string ConfirmPassword { get; set; }
    }

    public class SignUpUseCaseResult
    {
        public bool Success { get; set; }
        public string? ErrorMessage { get; set; }
    }

    public class SignUpHandler : IRequestHandler<SignUpUseCaseParameters, SignUpUseCaseResult>
    {
        private readonly DbManager _context;

        public SignUpHandler(DbManager context)
        {
            _context = context;
        }

        public async Task<SignUpUseCaseResult> Handle(SignUpUseCaseParameters parameters, CancellationToken cancellationToken)
        {
            var user = await _context.GetUser(parameters.Username);
            if (user != null)
            {
                return new SignUpUseCaseResult { Success = false, ErrorMessage = "User already exists" };
            }

            if (parameters.Password != parameters.ConfirmPassword)
            {
                return new SignUpUseCaseResult
                {
                    Success = false,
                    ErrorMessage = "Passwords do not match"
                };
            }
            var newUser = new User()
            {
                Id = Guid.NewGuid(),
                Email = parameters.Email,
                Username = parameters.Username
            };

            var passwordHash = PasswordHandler.HashPassword(parameters.Password);

            var password = new Password()
            {
                UserId = newUser.Id,
                PasswordHash = passwordHash
            };

            try
            {
                await _context.AddUser(newUser);
                await _context.AddPassword(password);
                await _context.SaveChangesAsync();
            }
            catch (Exception e)
            {
                return new SignUpUseCaseResult
                {
                    Success = false,
                    ErrorMessage = e.Message
                };
            }

            return new SignUpUseCaseResult
            {
                Success = true,
                ErrorMessage = null
            };
        }
    }
}
