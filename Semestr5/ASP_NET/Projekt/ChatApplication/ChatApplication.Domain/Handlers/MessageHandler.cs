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
        public List<MessageViewModel> Messages { get; set; }
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
            if (messages.Count == 0)
            {
                return new MessageUseCaseResult
                {
                    Messages = await convertToViewModel(messages),
                    Success = false,
                    ErrorMessage = "No messages found"
                };
            }
            return new MessageUseCaseResult
            {
                Messages = await convertToViewModel(messages),
                Success = true,
                ErrorMessage = ""
            };
        }
        private async Task<List<MessageViewModel>> convertToViewModel(List<Message> messages)
        {
            var messageViewModels = new List<MessageViewModel>();
            if(messages.Count == 0)
            {
                return messageViewModels;
            }
            else
            {
                foreach(var message in messages)
                {
                    var sender = await _context.GetUser(message.SenderId);
                    var receiver = await _context.GetUser(message.ReceiverId);

                    messageViewModels.Add(new MessageViewModel()
                    {
                        Content = message.Content,
                        Date = message.TimeSent,
                        Receiver = receiver.Username,
                        Sender = sender.Username
                    });
                }
            }
            return messageViewModels;
        }
    }
}
