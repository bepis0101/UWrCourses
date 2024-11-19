using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Task2.Models;

namespace Task2.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View(new HomeModel());
        }

        // POST: Home
        [HttpPost]
        public ActionResult Index(HomeModel homeModel)
        {
            if (ModelState.IsValid)
            {
                return RedirectToAction("Print", homeModel);
            }
            return View(homeModel);
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
