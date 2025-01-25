using ChatApplication.Domain.Handlers;
using ChatApplication.Models;
using MediatR;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.SignalR;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace ChatApplication.Hubs
{
    [Authorize]
    public class ChatHub : Hub
    {
        private readonly IMediator _mediator;

        public ChatHub(IMediator mediator)
        {
            _mediator = mediator;
        }

        public async Task SendMessage(string receiverUsername, string message)
        {
            var senderId = Context.User.FindFirstValue(ClaimTypes.NameIdentifier);

            var sender = await _mediator.Send(new UserUseCaseParameters { Id = senderId });
            var receiver = await _mediator.Send(new UserUseCaseParameters { Username = receiverUsername });
            
            if(!sender.Success || !receiver.Success)
            {
                return;
            }

            await Clients.User(receiver.FoundUser.Id.ToString()).SendAsync("ReceiveMessage", sender.FoundUser.Username, message);
            await Clients.User(sender.FoundUser.Id.ToString()).SendAsync("ReceiveMessage", sender.FoundUser.Username, message);

            var sentMessage = await _mediator
                .Send(new MessageSenderUseCaseParameters 
                { 
                    SenderId = sender.FoundUser.Id, 
                    ReceiverId = receiver.FoundUser.Id, 
                    Content = message
                });
        }
    }
}
