using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace lista8
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        bool player1Turn = true;
        private int cnt = 0;
        Button[,] buttons = new Button[3, 3];
        public MainWindow()
        {
            //InitializeComponent();
            InitializeButtonsArray();
        }

        private void InitializeButtonsArray()
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    buttons[i, j] = new Button();
                    buttons[i, j].Click += Button_Click;
                    Grid.SetRow(buttons[i, j], i);
                    Grid.SetColumn(buttons[i, j], j);
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            if (player1Turn)
            {
                button.Content = "X";
                buttons[Grid.GetRow(button), Grid.GetColumn(button)] = button;
                player1Turn = false;
            }
            else
            {
                button.Content = "O";
                buttons[Grid.GetRow(button), Grid.GetColumn(button)] = button;
                player1Turn = true;
            }
            button.IsEnabled = false;
            cnt++;
            if (cnt == 9)
            {
                MessageBox.Show("Remis");
                Close();
            }
            if (CheckWinner())
            {
                if (player1Turn)
                {
                    MessageBox.Show("Wygrał gracz 2");
                }
                else
                {
                    MessageBox.Show("Wygrał gracz 1");
                }
                Close();
            }
        }
        private bool CheckWinner()
        {
            for (int i = 0; i < 3; i++)
            {
                if (CheckRowCol(buttons[i, 0], buttons[i, 1], buttons[i, 2]))
                    return true;
            }

            // Sprawdzenie kolumn
            for (int i = 0; i < 3; i++)
            {
                if (CheckRowCol(buttons[0, i], buttons[1, i], buttons[2, i]))
                    return true;
            }

            // Sprawdzenie przekątnych
            if (CheckRowCol(buttons[0, 0], buttons[1, 1], buttons[2, 2]) || CheckRowCol(buttons[0, 2], buttons[1, 1], buttons[2, 0]))
                return true;

            return false;
        }
        private bool CheckRowCol(Button b1, Button b2, Button b3)
        {
            return b1.Content != null && b1.Content == b2.Content && b2.Content == b3.Content;
        }
        private void resetGame(object sender, RoutedEventArgs e)
        {
            cnt = 0;
            player1Turn = true;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    buttons[i, j].Content = null;
                    buttons[i, j].IsEnabled = true;
                }
            }
        }

    }
}