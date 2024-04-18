namespace lista6
{
    public partial class MainForm : Form
    {
        public string nameOfUni { get; set; }
        public string addressOfUni { get; set; }
        public string cycle { get; set; }
        public string type { get; set; }

        public MainForm()
        {
            InitializeComponent();
        }

        private void btCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void txtName_TextChanged(object sender, EventArgs e)
        {
            nameOfUni = this.txtName.Text;
            addressOfUni = this.txtAddress.Text;
        }

        private void btAcc_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            MessageBox.Show("Nazwa uczelni: " + nameOfUni + "\nAdres: " + addressOfUni + "\nCykl: " + cycle + "\nTyp: " + type);
            this.Close();
        }

        private void chocieCycle_SelectedIndexChanged(object sender, EventArgs e)
        {
            cycle = this.chocieCycle.Text;
        }

        private void chckDay_CheckedChanged(object sender, EventArgs e)
        {
            type = "Dzienne";
            this.chckUzup.Checked = false;
        }

        private void chckUzup_CheckedChanged(object sender, EventArgs e)
        {
            type = "Uzupe³niaj¹ce";
            this.chckDay.Checked = false;
        }

        private void txtAddress_TextChanged(object sender, EventArgs e)
        {
            this.addressOfUni = this.txtAddress.Text;
        }
    }
}
