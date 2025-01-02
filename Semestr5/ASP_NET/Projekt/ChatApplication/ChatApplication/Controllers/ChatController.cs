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


            var messages = mergeMessages(user.MessagesSent, user.MessagesReceived);

            return View(messages);

        }

        [HttpPost]
        public async Task<IActionResult> Send(MessageModel model)
        {
            if (!this.ModelState.IsValid)
            {
                return View("Index");
            }

            var receiver = await _context.Users.FirstOrDefaultAsync(u => u.Username == model.Receiver);
            var sender = await _context.Users.FirstOrDefaultAsync(u => u.Username == User.Identity.Name);

            var message = new Message()
            {
                MessageId = Guid.NewGuid(),
                Content = model.Content,
                TimeSent = DateTime.Now,
                ReceiverId = receiver.Id,
                SenderId = sender.Id,
            };

            _context.Messages.Add(message);
            await _context.SaveChangesAsync();
            return RedirectToAction("Index", receiver.Id);
        }
        private List<Message> mergeMessages(ICollection<Message> sent, ICollection<Message> received)
        {
            var messages = new List<Message>();
            if (sent != null && sent.Any())
            {
                foreach (var message in sent)
                {
                    messages.Add(message);
                }
            }
            if( received != null && received.Any())
            {
                foreach (var message in received)
                {
                    messages.Add(message);
                }

            }
            return messages.OrderBy(m => m.TimeSent).ToList();
        }
    }
}
