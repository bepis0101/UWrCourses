namespace lista7
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Text = "Form1";
            this.panelClock = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer();
            this.SuspendLayout();
            // 
            // panelClock
            // 
            this.panelClock.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelClock.Location = new System.Drawing.Point(0, 0);
            this.panelClock.Name = "panelClock";
            this.panelClock.Size = new System.Drawing.Size(800, 450);
            this.panelClock.TabIndex = 0;
            this.panelClock.Paint += new System.Windows.Forms.PaintEventHandler(this.PanelClock_Paint);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.panelClock);
            this.Name = "MainForm";
            this.Text = "Analog Clock";
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            this.ResumeLayout(false);
        }

        #endregion
        private System.Windows.Forms.Panel panelClock;
        private System.Windows.Forms.Timer timer1;
    }
}
