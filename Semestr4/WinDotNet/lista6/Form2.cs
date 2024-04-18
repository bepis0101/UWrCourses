using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lista6
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            this.contextMenuStrip2.Show(this, 10, 20);

        }

        private void toolStripButton1_MouseHover(object sender, EventArgs e)
        {
            this.toolTip1.Show("click", this);
        }

    }
}
