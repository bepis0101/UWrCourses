﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista9_2.Models
{
    public class Child
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public int ParentId { get; set; }
        public Parent Parent { get; set; }
    }
}
