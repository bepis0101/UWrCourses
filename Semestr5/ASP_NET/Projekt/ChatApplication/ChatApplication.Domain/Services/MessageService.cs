using ChatApplication.Domain.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatApplication.Domain.Services
{
    public static class MessageService
    {
        public static List<Message> mergeMessages(List<Message>? messagesSent, List<Message>? messagesReceived)
        {
            if(messagesSent == null && messagesReceived == null)
            {
                return new List<Message>();
            }

            if (messagesReceived == null)
            {
                messagesSent.Sort((x, y) => x.TimeSent.CompareTo(y.TimeSent));
                return messagesSent;
            }
            if (messagesSent == null)
            {
                messagesReceived.Sort((x, y) => x.TimeSent.CompareTo(y.TimeSent));
                return messagesReceived;
            }

            var messages = messagesSent.Concat(messagesReceived).ToList();
            messages.Sort((x, y) => x.TimeSent.CompareTo(y.TimeSent));
            return messages;
        }
    }
}
