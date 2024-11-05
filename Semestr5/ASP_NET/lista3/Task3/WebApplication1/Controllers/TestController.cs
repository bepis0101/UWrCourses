using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class TestController : Controller
    {
        // GET: Test
        public ActionResult Index()
        {
            var headers = Request.Headers;
            foreach (var header in headers.AllKeys)
            {
                Response.Write(header + ": " + headers[header] + "<br>");
            }
            Response.Write("Hello World");
            Response.AddHeader("CustomHeader", "CustomHeaderValue");
            

            var path = Server.MapPath("~/");
            Response.Write(path);
            return View();
        }
    }

    // HTTPContextCurrent pozwala na dostep do informacji
    // o kontekscie rzadabua w dowolym miejscu kodu

}