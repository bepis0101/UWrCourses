using ChatApplication.Domain.Models;

namespace ChatApplication.Models
{
    public class ChatModel : ErrorModel
    {
        public List<MessageViewModel> Messages { get; set; }
        public string ReceiverUsername { get; set; }
    }
}
