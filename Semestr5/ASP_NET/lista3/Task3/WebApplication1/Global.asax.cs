using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using WebApplication1.Utils;

namespace WebApplication1
{
    public class MvcApplication : System.Web.HttpApplication
    {
        const string singl = "Singleton";
        public static string Singleton
        {
            get
            {
                if (HttpContext.Current.Application[singl] == null)
                {
                    lock (HttpContext.Current.Application)
                    {
                        if (HttpContext.Current.Application[singl] == null)
                        {
                            HttpContext.Current.Application[singl] = "Singleton";
                        }
                    }
                }
                return (string)HttpContext.Current.Application[singl];
            }
        }
        protected void Application_Start()
        {
            AreaRegistration.RegisterAllAreas();
            RouteConfig.RegisterRoutes(RouteTable.Routes);  
            HttpContext.Current.Application["Counter"] = 0;
        }

        protected void Application_End()
        {
            HttpContext.Current.Application.Remove(singl);
            HttpContext.Current.Application[singl] = null;
            DbContextManager.DisposeContext();
        }
    }
}
