using ChatApplication.Models;
using ChatApplication.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.SignalR;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace ChatApplication.Hubs
{
    [Authorize]
    public class ChatHub : Hub
    {
        private readonly DbManager _context;

        public ChatHub(DbManager context)
        {
            _context = context;
        }

        public async Task SendMessage(string receiverUsername, string message)
        {
            var senderId = Context.User.FindFirstValue(ClaimTypes.NameIdentifier);

            var sender = await _context.Users.FirstOrDefaultAsync(u => u.Id == Guid.Parse(senderId));
            var receiver = await _context.Users.FirstOrDefaultAsync(u => u.Username == receiverUsername);
            
            await Clients.User(receiver.Id.ToString()).SendAsync("ReceiveMessage", sender.Username, message);
            await Clients.User(sender.Id.ToString()).SendAsync("ReceiveMessage", sender.Username, message);

            if (sender != null && receiver != null)
            {
                var newMessage = new Message
                {
                    MessageId = Guid.NewGuid(),
                    Content = message,
                    TimeSent = DateTime.Now,
                    SenderId = sender.Id,
                    ReceiverId = receiver.Id
                };

                _context.Messages.Add(newMessage);
                await _context.SaveChangesAsync();

            }
        }
    }
}
