using ChatApplication.Domain.Models;
using ChatApplication.Domain.Services;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ChatApplication.Domain
{
    public class DbManager : DbContext
    {
        public DbManager(DbContextOptions options) : base(options)
        {

        }

        public DbSet<User> Users { get; set; }
        public DbSet<Password> Passwords { get; set; }
        public DbSet<Message> Messages { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>().ToTable("User");
            modelBuilder.Entity<Password>().ToTable("Password");
            modelBuilder.Entity<Message>().ToTable("Message");

            modelBuilder.Entity<Message>()
                .HasOne(m => m.Sender)
                .WithMany(u => u.MessagesSent)
                .HasForeignKey(m => m.SenderId);

            modelBuilder.Entity<Message>()
                .HasOne(m => m.Receiver)
                .WithMany(u => u.MessagesReceived)
                .HasForeignKey(m => m.ReceiverId);
            modelBuilder.Entity<User>()
                .HasMany(u => u.MessagesSent)
                .WithOne(m => m.Sender)
                .HasForeignKey(m => m.SenderId);
            modelBuilder.Entity<User>()
                .HasMany(u => u.MessagesReceived)
                .WithOne(m => m.Receiver)
                .HasForeignKey(m => m.ReceiverId);
        }

        public async Task<User?> GetUser(Guid Id)
        {
            return await Users.FirstOrDefaultAsync(u => u.Id == Id);
        }

        public async Task<User?> GetUser(string username)
        {
            return await Users.FirstOrDefaultAsync(u => u.Username == username);
        }

        public async Task<Password?> GetPassword(Guid UserId)
        {
            return await Passwords.FirstOrDefaultAsync(p => p.UserId == UserId);
        }

        public async Task<List<Message>?> GetMessages(Guid senderId, Guid receiverId)
        {
            var sent = await Messages.Where(m => m.SenderId == senderId && m.ReceiverId == receiverId).ToListAsync();
            var received = await Messages.Where(m => m.SenderId == receiverId && m.ReceiverId == senderId).ToListAsync();
            return MessageService.mergeMessages(sent, received);
        }

        public async Task AddMessage(Message message)
        {
            await Messages.AddAsync(message);
        }

        public async Task AddUser(User user)
        {
            await Users.AddAsync(user);
        }
        public async Task AddPassword(Password password)
        {
            await Passwords.AddAsync(password);
        }
        public async Task<List<User>?> GetUsersExcept(Guid Id)
        {
            return await Users.Where(u => u.Id != Id).ToListAsync();
        }
    }
}
