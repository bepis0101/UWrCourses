using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace auth.Models
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            string username = TextBox1.Text;
            string password = TextBox2.Text;

            if (username == "admin" && password == "admin")
            {
                Session["User"] = username;
                string returnUrl = Request.QueryString["ReturnUrl"];
                if (returnUrl != null)
                {
                    Response.Redirect(returnUrl);
                }
                else
                {
                    Response.Redirect("Home.aspx");
                }
            }
            else
            {
                Label1.Text = "Invalid username or password";
            }
        }
    }
}