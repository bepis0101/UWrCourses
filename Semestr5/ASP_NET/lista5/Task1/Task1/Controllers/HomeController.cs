using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Task1.Models;

namespace Task1.Controllers
{
    public class HomeController : Controller
    {
        // GET: Home
        public ActionResult Index()
        {
            var model = new HomeModel();
            model.TaskPoints = new int[10];
            return View(model);
        }

        // POST: Home
        [HttpPost]
        public ActionResult Index(HomeModel model)
        {
            if (ModelState.IsValid)
            {
                return RedirectToAction("Print", model);
            }
            else
            {                
                return View(model);
            }
        }

        // GET: Print
        public ActionResult Print(HomeModel homeModel)
        {
            if (homeModel == null)
            {
                return RedirectToAction("Index");
            }
            return View(homeModel);
        }
    }
}