using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class DefaultController : Controller
    {
        // GET: Default
        public ActionResult Index()
        {
            lock(HttpContext.Application)
            {
                HttpContext.Application["Counter"] = (int)HttpContext.Application["Counter"] + 1;
                Response.Write("Counter: " + HttpContext.Application["Counter"]);
            }
            if (Session["Counter"] == null)
            {
                Session["Counter"] = 0;
            }
            Session["Counter"] = (int)Session["Counter"] + 1;
            Response.Write("\nSessionCounter: " + Session["Counter"]);
            Response.End();
            // items zmienna lokalna
            return View();
        }
    }
}