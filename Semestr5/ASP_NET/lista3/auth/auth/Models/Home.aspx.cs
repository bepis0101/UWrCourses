using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace auth.Models
{
    public partial class Home : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["User"] == null)
            {
                string returnUrl = Request.QueryString["ReturnUrl"];
                if (returnUrl != null)
                {
                    Response.Redirect("Login.aspx?ReturnUrl=" + returnUrl);
                }
                else
                {
                    Response.Redirect("Login.aspx");
                }
            }
        }
    }
}