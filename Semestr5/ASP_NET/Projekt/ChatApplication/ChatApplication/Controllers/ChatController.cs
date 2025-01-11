using ChatApplication.Models;
using ChatApplication.Domain;
using ChatApplication.Domain.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;
using MediatR;
using ChatApplication.Domain.Handler;

namespace ChatApplication.Controllers
{
    [Authorize]
    public class ChatController : Controller
    {

        private readonly IMediator _mediator;
        
        public ChatController(IMediator mediator)
        {
            _mediator = mediator;
        }

        [HttpGet]
        public async Task<IActionResult> Index()
        {
            var Id = User.FindFirstValue(ClaimTypes.NameIdentifier);
            var chatParameters = new ChatUseCaseParameters()
            {
                UserId = Guid.Parse(Id)
            };
            var result = await _mediator.Send(chatParameters);
            if(result.Success == false)
            {
                return RedirectToAction("Index", "Home");
            }
            var allUsers = new List<UserViewModel>();
            foreach (var user in result.Chats)
            {
                allUsers.Add(new UserViewModel()
                {
                    Id = user.Id,
                    Username = user.Username,
                    Email = user.Email
                });
            }
            return View(allUsers);
        }

        [HttpGet]
        public async Task<IActionResult> Chat(Guid Id)
        {
            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);

            var messageParameters = new MessageUseCaseParameters()
            {
                SenderId = Guid.Parse(userId),
                ReceiverId = Id
            };

            var result = await _mediator.Send(messageParameters);
            if(result.Success == false)
            {
                return RedirectToAction("Index", "Chat");
            }

            return View(MergeMessages(result.Messages));

        }

        private List<MessageModel> MergeMessages(List<Message> messages)
        {
            var messageModels = new List<MessageModel>();
            foreach (var message in messages)
            {
                messageModels.Add(new MessageModel()
                {
                    Content = message.Content,
                    Date = message.TimeSent,
                    Sender = message.Sender.Username,
                    Receiver = message.Receiver.Username
                });
            }
            return messageModels;
        }
    }
}
