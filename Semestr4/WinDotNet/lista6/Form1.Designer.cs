namespace lista6
{
    partial class MainForm
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
            groupBox1 = new GroupBox();
            label2 = new Label();
            label1 = new Label();
            txtAddress = new TextBox();
            txtName = new TextBox();
            groupBox2 = new GroupBox();
            chckUzup = new CheckBox();
            chckDay = new CheckBox();
            chocieCycle = new ComboBox();
            label3 = new Label();
            btAcc = new Button();
            btCancel = new Button();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            SuspendLayout();
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(label2);
            groupBox1.Controls.Add(label1);
            groupBox1.Controls.Add(txtAddress);
            groupBox1.Controls.Add(txtName);
            groupBox1.Location = new Point(12, 16);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(776, 191);
            groupBox1.TabIndex = 0;
            groupBox1.TabStop = false;
            groupBox1.Text = "Uczelnia";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 120);
            label2.Name = "label2";
            label2.Size = new Size(62, 25);
            label2.TabIndex = 6;
            label2.Text = "Adres:";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 54);
            label1.Name = "label1";
            label1.Size = new Size(68, 25);
            label1.TabIndex = 5;
            label1.Text = "Nazwa:";
            // 
            // txtAddress
            // 
            txtAddress.Location = new Point(115, 114);
            txtAddress.Name = "txtAddress";
            txtAddress.Size = new Size(330, 31);
            txtAddress.TabIndex = 4;
            txtAddress.TextChanged += txtAddress_TextChanged;
            // 
            // txtName
            // 
            txtName.Location = new Point(115, 48);
            txtName.Name = "txtName";
            txtName.Size = new Size(330, 31);
            txtName.TabIndex = 3;
            txtName.TextChanged += txtName_TextChanged;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(chckUzup);
            groupBox2.Controls.Add(chckDay);
            groupBox2.Controls.Add(chocieCycle);
            groupBox2.Controls.Add(label3);
            groupBox2.Location = new Point(12, 213);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(776, 196);
            groupBox2.TabIndex = 0;
            groupBox2.TabStop = false;
            groupBox2.Text = "Rodzaj studiów";
            // 
            // chckUzup
            // 
            chckUzup.AutoSize = true;
            chckUzup.Location = new Point(222, 151);
            chckUzup.Name = "chckUzup";
            chckUzup.Size = new Size(144, 29);
            chckUzup.TabIndex = 3;
            chckUzup.Text = "uzupełniające";
            chckUzup.UseVisualStyleBackColor = true;
            chckUzup.CheckedChanged += chckUzup_CheckedChanged;
            // 
            // chckDay
            // 
            chckDay.AutoSize = true;
            chckDay.Location = new Point(117, 151);
            chckDay.Name = "chckDay";
            chckDay.Size = new Size(99, 29);
            chckDay.TabIndex = 2;
            chckDay.Text = "dzienne";
            chckDay.UseVisualStyleBackColor = true;
            chckDay.CheckedChanged += chckDay_CheckedChanged;
            // 
            // chocieCycle
            // 
            chocieCycle.FormattingEnabled = true;
            chocieCycle.Items.AddRange(new object[] { "Informatyka I stopnia 3 lata", "Informatyka I stopnia inżynierska", "Informaytyka II stopnia magisterska", "ISIM", "Data Science" });
            chocieCycle.Location = new Point(115, 68);
            chocieCycle.Name = "chocieCycle";
            chocieCycle.Size = new Size(309, 33);
            chocieCycle.TabIndex = 1;
            chocieCycle.SelectedIndexChanged += chocieCycle_SelectedIndexChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(6, 71);
            label3.Name = "label3";
            label3.Size = new Size(96, 25);
            label3.TabIndex = 0;
            label3.Text = "Cykl nauki:";
            // 
            // btAcc
            // 
            btAcc.Location = new Point(12, 415);
            btAcc.Name = "btAcc";
            btAcc.Size = new Size(112, 34);
            btAcc.TabIndex = 1;
            btAcc.Text = "Akceptuj";
            btAcc.UseVisualStyleBackColor = true;
            btAcc.Click += btAcc_Click;
            // 
            // btCancel
            // 
            btCancel.Location = new Point(676, 415);
            btCancel.Name = "btCancel";
            btCancel.Size = new Size(112, 34);
            btCancel.TabIndex = 2;
            btCancel.Text = "Anuluj";
            btCancel.UseVisualStyleBackColor = true;
            btCancel.Click += btCancel_Click;
            // 
            // MainForm
            // 
            AcceptButton = btAcc;
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            CancelButton = btCancel;
            ClientSize = new Size(800, 450);
            Controls.Add(btCancel);
            Controls.Add(btAcc);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Name = "MainForm";
            Text = "Wybór uczelni";
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private Button btAcc;
        private Button btCancel;
        private TextBox txtAddress;
        private TextBox txtName;
        private Label label1;
        private Label label2;
        private CheckBox chckUzup;
        private CheckBox chckDay;
        private ComboBox chocieCycle;
        private Label label3;
    }
}
