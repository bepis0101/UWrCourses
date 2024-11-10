using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;

namespace Taks4Framework.Controllers
{
    public class ConfigTest
    {
        public string Test()
        {
            return ConfigurationManager.AppSettings["test"];
        }

    }
}