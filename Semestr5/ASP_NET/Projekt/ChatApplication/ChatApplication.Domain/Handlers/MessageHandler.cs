using ChatApplication.Domain.Models;
using ChatApplication.Domain.Services;
using MediatR;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Handler
{
    public class MessageUseCaseParameters: IRequest<MessageUseCaseResult>
    {
        public Guid SenderId { get; set; }
        public Guid ReceiverId { get; set; }

    }
    public class MessageUseCaseResult
    {
        public List<Message> Messages { get; set; }
        public bool Success { get; set; }
        public string? ErrorMessage { get; set; }
    }

    public class MessageHandler : IRequestHandler<MessageUseCaseParameters, MessageUseCaseResult>
    {
        private readonly DbManager _context;
        public MessageHandler(DbManager context)
        {
            _context = context;
        }
        public async Task<MessageUseCaseResult> Handle(MessageUseCaseParameters parameters, CancellationToken token)
        {
            var receivedMessages = await _context.GetMessages(parameters.SenderId, parameters.ReceiverId);
            var sentMessages = await _context.GetMessages(parameters.ReceiverId, parameters.SenderId);
            var messages = MessageService.mergeMessages(receivedMessages, sentMessages);
            if (messages.IsNullOrEmpty())
            {
                return new MessageUseCaseResult
                {
                    Messages = messages,
                    Success = false,
                    ErrorMessage = "No messages found"
                };
            }
            return new MessageUseCaseResult
            {
                Messages = messages,
                Success = true,
                ErrorMessage = ""
            };
        }
    }
}
