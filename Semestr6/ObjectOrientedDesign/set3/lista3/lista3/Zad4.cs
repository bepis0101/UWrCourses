using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista3
{
    public interface IShape
    {
        int CalculateArea();
    }

    public class Rectangle : IShape
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public int CalculateArea()
        {
            return Width * Height;
        }
    }
    public class Square : IShape
    {
        public int Side { get; set; }

        public int CalculateArea()
        {
            return Side * Side;
        }
    }
    public class AreaCalculator
    {
        public int CalculateArea(IShape shape)
        {
            return shape.CalculateArea();
        }
    }

    class Zad4
    {
        public static void Main(string[] args)
        {
            int w = 4, h = 5;

            var rectangle = new Rectangle { Width = w, Height = h };
            var square = new Square { Side = w };

            var calc = new AreaCalculator();

            Console.WriteLine("Prostokąt o wymiarach {0} na {1} ma pole {2}",
                w, h, calc.CalculateArea(rectangle));

            Console.WriteLine("Kwadrat o boku {0} ma pole {1}",
                w, calc.CalculateArea(square));
        }
    }
}
