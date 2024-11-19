using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Task1.Models
{
    public class HomeModel
    {
        [Required(ErrorMessage = "Name is required")]
        public string Name { get; set; }
        [Required(ErrorMessage = "Surname is required")]
        public string Surname { get; set; }
        [Required(ErrorMessage = "Date is required")]
        public DateTime Date { get; set; }
        [Required(ErrorMessage = "Name of course is required")]
        public string NameOfCourse { get; set; }
        [Required(ErrorMessage = "List number is required")]
        public int ListNumber { get; set; }
        public int[] TaskPoints { get; set; }
        public HomeModel() 
        {
            //TaskPoints = new List<int>(new int[10]);
        }

    }
}