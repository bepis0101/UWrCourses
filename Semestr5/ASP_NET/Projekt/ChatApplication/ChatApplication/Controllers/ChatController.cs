using Azure.Messaging;
using ChatApplication.Models;
using ChatApplication.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace ChatApplication.Controllers
{
    [Authorize]
    public class ChatController : Controller
    {

        private readonly DbManager _context;
        public ChatController(DbManager context)
        {
            _context = context;
        }

        [HttpGet]
        public IActionResult Index()
        {
            var allUsers = _context.Users.ToList();
            return View(allUsers);
        }

        [HttpGet]
        public async Task<IActionResult> Chat(Guid Id)
        {
            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);

            var user = await _context.Users.FirstOrDefaultAsync(u => u.Id == Guid.Parse(userId));
            var receiver = await _context.Users.FirstOrDefaultAsync(u => u.Id == Id);

            if (user == null)
            {
                return RedirectToAction("Index");
            }
            if (receiver == null)
            {
                return RedirectToAction("Index");
            }
            var messagesSent = await _context.Messages.Where(m => m.SenderId == user.Id && m.ReceiverId == receiver.Id).ToListAsync();
            var messagesReceived = await _context.Messages.Where(m => m.SenderId == receiver.Id && m.ReceiverId == user.Id).ToListAsync();



            var messages = new ChatModel()
            {
                Messages = mergeMessages(messagesSent, messagesReceived),
                ReceiverUsername = receiver.Username
            };

            return View(messages);

        }

        private List<MessageModel> mergeMessages(ICollection<Message> sent, ICollection<Message> received)
        {
            var messages = new List<MessageModel>();
            if (sent != null && sent.Any())
            {
                foreach (var message in sent)
                {
                    messages.Add(new MessageModel()
                    {
                        Receiver = message.Receiver.Username,
                        Sender = message.Sender.Username,
                        Content = message.Content,
                        Date = message.TimeSent
                    });
                }
            }
            if(received != null && received.Any())
            {
                foreach (var message in received)
                {
                    messages.Add(new MessageModel()
                    {
                        Receiver = message.Receiver.Username,
                        Sender = message.Sender.Username,
                        Content = message.Content,
                        Date = message.TimeSent
                    });
                }
            }
            messages.Sort((x, y) => x.Date.CompareTo(y.Date));

            return messages;
        }
    }
}
