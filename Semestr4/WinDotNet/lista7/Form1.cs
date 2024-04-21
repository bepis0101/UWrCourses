using System;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace lista7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            timer1.Interval = 1000;
            timer1.Tick += Timer1_Tick;
            timer1.Start();
        }
        private void Timer1_Tick(object sender, EventArgs e)
        {
            // Wywo³anie metody Invalidate() powoduje odrysowanie kontrolki Panel
            panelClock.Invalidate();
        }
        private void PanelClock_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            // Ustawienie wyg³adzania rysowania
            g.SmoothingMode = SmoothingMode.AntiAlias;

            // Pobranie wymiarów panelu
            int width = panelClock.Width;
            int height = panelClock.Height;

            // Obliczenie œrodka panelu
            int centerX = width / 2;
            int centerY = height / 2;

            // Obliczenie promienia zegara
            int radius = Math.Min(width, height) / 2 - 10;

            // Narysowanie tarczy zegara
            g.FillEllipse(Brushes.White, centerX - radius, centerY - radius, 2 * radius, 2 * radius);
            g.DrawEllipse(Pens.Black, centerX - radius, centerY - radius, 2 * radius, 2 * radius);

            // Narysowanie cyfr na tarczy zegara
            for (int i = 1; i <= 12; i++)
            {
                double angle = i * 30 * Math.PI / 180;
                int numX = centerX + (int)((radius - 20) * Math.Sin(angle));
                int numY = centerY - (int)((radius - 20) * Math.Cos(angle));
                g.DrawString(i.ToString(), this.Font, Brushes.Black, numX, numY, new StringFormat() { Alignment = StringAlignment.Center, LineAlignment = StringAlignment.Center });
            }

            // Pobranie aktualnej godziny
            DateTime now = DateTime.Now;
            int hour = now.Hour % 12;
            int minute = now.Minute;
            int second = now.Second;

            // Narysowanie wskazówki godzinowej
            double hourAngle = (hour * 30 + minute * 0.5) * Math.PI / 180;
            int hourLength = radius - radius / 2;
            int hourX = centerX + (int)(hourLength * Math.Sin(hourAngle));
            int hourY = centerY - (int)(hourLength * Math.Cos(hourAngle));
            g.DrawLine(Pens.Black, centerX, centerY, hourX, hourY);

            // Narysowanie wskazówki minutowej
            double minuteAngle = (minute * 6 + second * 0.1) * Math.PI / 180;
            int minuteLength = radius - radius / 4;
            int minuteX = centerX + (int)(minuteLength * Math.Sin(minuteAngle));
            int minuteY = centerY - (int)(minuteLength * Math.Cos(minuteAngle));
            g.DrawLine(Pens.Black, centerX, centerY, minuteX, minuteY);

            // Narysowanie wskazówki sekundowej
            double secondAngle = second * 6 * Math.PI / 180;
            int secondLength = radius - 5;
            int secondX = centerX + (int)(secondLength * Math.Sin(secondAngle));
            int secondY = centerY - (int)(secondLength * Math.Cos(secondAngle));
            g.DrawLine(Pens.Red, centerX, centerY, secondX, secondY);
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            // Ponowne rysowanie zegara po zmianie rozmiaru okna
            panelClock.Invalidate();
        }
    }
}
