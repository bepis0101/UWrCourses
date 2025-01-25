using ChatApplication.Domain.Models;
using MediatR;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion.Internal;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Handlers
{
    public class UserUseCaseParameters : IRequest<UserUseCaseResult>
    {
        public string? Username { get; set; }
        public string? Id { get; set; }
    }
    public class UserUseCaseResult
    {
        public User? FoundUser { get; set; }
        public bool Success { get; set; }
        public string? ErrorMessage { get; set; }
    }
    public class UserHandler : IRequestHandler<UserUseCaseParameters, UserUseCaseResult>
    {
        private readonly DbManager _context;
        public UserHandler(DbManager context) 
        {
            _context = context;
        }

        public async Task<UserUseCaseResult> Handle(UserUseCaseParameters request, CancellationToken cancellationToken)
        {
            if(request.Id == null)
            {
                var user = await _context.GetUser(request.Username);
                if (user == null)
                {
                    return new UserUseCaseResult
                    {
                        FoundUser = null,
                        Success = false,
                        ErrorMessage = "Internal server error"
                    };
                }
                return new UserUseCaseResult
                {
                    FoundUser = user,
                    Success = true,
                    ErrorMessage = ""
                };
            }
            else
            {
                var user = await _context.GetUser(Guid.Parse(request.Id));
                if (user == null)
                {
                    return new UserUseCaseResult
                    {
                        FoundUser = null,
                        Success = false,
                        ErrorMessage = "Internal server error"
                    };
                }
                return new UserUseCaseResult
                {
                    FoundUser = user,
                    Success = true,
                    ErrorMessage = ""
                };
            }
        }
    }
}
