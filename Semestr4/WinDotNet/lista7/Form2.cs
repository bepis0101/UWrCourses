using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lista7
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            SetStyle(ControlStyles.ResizeRedraw, true);
        }
        private int _minimum = 0;
        private int _maximum = 100;
        private int _value = 10;

        public int Minimum
        {
            get { return _minimum; }
            set
            {
                if (value < 0)
                    throw new ArgumentException("Minimum value cannot be less than zero.");
                _minimum = value;
                Invalidate();
            }
        }

        public int Maximum
        {
            get { return _maximum; }
            set
            {
                if (value < _minimum)
                    throw new ArgumentException("Maximum value cannot be less than minimum value.");
                _maximum = value;
                Invalidate();
            }
        }

        public int Value
        {
            get { return _value; }
            set
            {
                if (value < _minimum || value > _maximum)
                    throw new ArgumentException("Value must be between minimum and maximum values.");
                _value = value;
                Invalidate();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;

            // Rysowanie gradientowego tła
            using (LinearGradientBrush brush = new LinearGradientBrush(ClientRectangle, Color.LightBlue, Color.DarkBlue, LinearGradientMode.Vertical))
            {
                g.FillRectangle(brush, ClientRectangle);
            }

            // Rysowanie obramowania
            using (Pen pen = new Pen(Color.Black))
            {
                g.DrawRectangle(pen, ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width - 1, ClientRectangle.Height - 1);
            }

            // Obliczanie długości paska postępu
            float progressWidth = (float)(_value - _minimum) / (_maximum - _minimum) * Width;

            // Rysowanie paska postępu
            using (SolidBrush brush = new SolidBrush(Color.FromArgb(100, Color.White)))
            {
                g.FillRectangle(brush, ClientRectangle.X, ClientRectangle.Y, progressWidth, ClientRectangle.Height);
            }

            // Rysowanie procentowego wskaźnika postępu w środku paska
            string percentage = $"{(_value - _minimum) * 100 / (_maximum - _minimum)}%";
            using (Font font = new Font(FontFamily.GenericSansSerif, 10))
            {
                SizeF textSize = g.MeasureString(percentage, font);
                PointF textLocation = new PointF((Width - textSize.Width) / 2, (Height - textSize.Height) / 2);
                g.DrawString(percentage, font, Brushes.Black, textLocation);
            }
        }
    }
}
