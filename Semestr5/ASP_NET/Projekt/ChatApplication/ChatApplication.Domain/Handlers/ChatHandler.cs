using ChatApplication.Domain.Models;
using MediatR;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Handler
{
    public class ChatUseCaseParameters : IRequest<ChatUseCaseResult>
    {
        public Guid UserId { get; set; }
    }
    

    public class ChatUseCaseResult
    {
        public List<User>? Chats { get; set; }
        public bool Success { get; set; }
        public string? ErrorMessage { get; set; }
    }
    public class ChatHandler : IRequestHandler<ChatUseCaseParameters, ChatUseCaseResult>
    {
        private readonly DbManager _context;
        public ChatHandler(DbManager context)
        {
            _context = context;
        }

        public async Task<ChatUseCaseResult> Handle(ChatUseCaseParameters parameters, CancellationToken token)
        {
            var users = await _context.GetUsersExcept(parameters.UserId);
            
            if(users.IsNullOrEmpty())
            {
                return new ChatUseCaseResult
                {
                    Chats = users,
                    Success = false,
                    ErrorMessage = "No users found"
                };
            }
            return new ChatUseCaseResult
            {
                Chats = users,
                Success = true,
                ErrorMessage = ""
            };
        }

    }
}
