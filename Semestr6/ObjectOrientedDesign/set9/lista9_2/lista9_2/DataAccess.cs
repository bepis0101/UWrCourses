using lista9_2.Models;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista9_2
{
    public class DataAccess : DbContext
    {
        public DbSet<Parent> Parents { get; set; }
        public DbSet<Child> Children { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder options)
        {
            options.UseSqlite("Data Source=example.db");
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder
                .Entity<Parent>()
                .HasMany(p => p.Children)
                .WithOne(p => p.Parent)
                .HasForeignKey(p => p.ParentId);
        }
    }
}
