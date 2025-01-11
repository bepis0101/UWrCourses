using ChatApplication.Domain.Models;
using MediatR;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Handlers
{
    public class MessageSenderUseCaseParameters : IRequest<MessageSenderUseCaseResult>
    {
        public Guid SenderId { get; set; }
        public Guid ReceiverId { get; set; }
        public string? Content { get; set; }
    }

    public class MessageSenderUseCaseResult
    {
        public bool Success { get; set; }
        public string? ErrorMessage { get; set; }
    }

    public class MessageSenderHandler : IRequestHandler<MessageSenderUseCaseParameters, MessageSenderUseCaseResult>
    {
        private readonly DbManager _context;
        public MessageSenderHandler(DbManager context)
        {
            _context = context;
        }

        public async Task<MessageSenderUseCaseResult> Handle(MessageSenderUseCaseParameters request, CancellationToken cancellationToken)
        {
            if (request.Content.IsNullOrEmpty())
            {
                return new MessageSenderUseCaseResult
                {
                    Success = false,
                    ErrorMessage = "Message content cannot be empty"
                };
            }

            var message = new Message
            {
                SenderId = request.SenderId,
                ReceiverId = request.ReceiverId,
                Content = request.Content
            };

            await _context.AddMessage(message);
            await _context.SaveChangesAsync();

            return new MessageSenderUseCaseResult
            {
                Success = true,
                ErrorMessage = ""
            };
        }

    }
}
