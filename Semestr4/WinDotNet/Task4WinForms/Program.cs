using System.Globalization;

namespace Task4WinForms
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            //Application.Run(new Form1());
            App();
        }

        static void App()
        {
            string[] cultures = { "en", "de", "fr", "ru", "ar", "cs", "pl", "he" };

            foreach (string culture in cultures)
            {
                CultureInfo cultureInfo = new CultureInfo(culture);

                string monthsFull = string.Join(", ", cultureInfo.DateTimeFormat.MonthNames);
                string monthsShort = string.Join(", ", cultureInfo.DateTimeFormat.AbbreviatedMonthNames);

                string daysFull = string.Join(", ", cultureInfo.DateTimeFormat.DayNames);
                string daysShort = string.Join(", ", cultureInfo.DateTimeFormat.AbbreviatedDayNames);

                string currentDate = DateTime.Now.ToString("D", cultureInfo);


                string infoMessage = $"nazwa kultury: {cultureInfo.DisplayName}\n" +
                                        $"miesiące pełne: {monthsFull}\n" +
                                        $"miesiące krótkie: {monthsShort}\n" +
                                        $"dni pełne: {daysFull}\n" +
                                        $"dni któtkie: {daysShort}\n" +
                                        $"bieżąca data: {currentDate}";

                if (culture == "ar" || culture == "ru" || culture == "he")
                {
                    MessageBox.Show(infoMessage, "Informacje o dacie", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    Console.WriteLine(infoMessage);
                }
            }

        }
    }
}