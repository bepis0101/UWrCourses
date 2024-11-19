using System.ComponentModel.DataAnnotations;

namespace WebApplication1.Models
{
    public class BookModel
    {
        [Required]
        public Guid ID { get; set; }
        [Required]
        public string Title { get; set; }
        [Required]
        public string Author { get; set; }
        [Required]
        public string ISBN { get; set; }
        [Required]
        public int YearOfRelease { get; set; }
    }
}
