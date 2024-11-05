using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;

namespace WebApplication1.Utils
{
    public class DbContextManager
    {
        private const string DbContextKey = "DbContext";
        public static SqlConnection Current
        {
            get
            {
                if (HttpContext.Current.Items[DbContextKey] == null)
                {
                    var connection = new SqlConnection("constring");
                    connection.Open();
                    HttpContext.Current.Items[DbContextKey] = connection;
                }
                return (SqlConnection)HttpContext.Current.Items[DbContextKey];

            }
        }
        public static void DisposeContext()
        {
            if (HttpContext.Current.Items[DbContextKey] != null)
            {
                var connection = (SqlConnection)HttpContext.Current.Items[DbContextKey];
                connection.Close();
                connection.Dispose();
            }
        }
    }
}