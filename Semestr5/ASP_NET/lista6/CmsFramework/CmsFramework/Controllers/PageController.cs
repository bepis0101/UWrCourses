using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CmsFramework.Controllers
{
    public class PageController : Controller
    {
        // GET: Page
        public ActionResult Render()
        {
            var routeData = this.Request.RequestContext.RouteData.Values;
            var siteName = routeData["siteName"] as string;
            var pageName = routeData["pageName"] as string;

            var model = new PageRenderModel
            {
                SiteName = siteName,
                PageName = pageName
            };
            return View(model);
        }
    }
    public class PageRenderModel
    {
        public string SiteName { get; set; }
        public string PageName { get; set; }
    }

}