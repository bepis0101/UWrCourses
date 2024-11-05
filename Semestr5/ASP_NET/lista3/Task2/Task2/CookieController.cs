using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Task2
{
    [Route("api/[controller]")]
    [ApiController]
    public class CookieController : ControllerBase
    {
        private const string CookieName = "MyCookie";
        [HttpPost("add")]
        public IActionResult AddCookie()
        {
            var cookieOptions = new CookieOptions
            {
                Expires = System.DateTime.Now.AddMinutes(10),
                HttpOnly = true,
                Secure = true,
            };

            Response.Cookies.Append(CookieName, "MyValue", cookieOptions);
            return Ok("Cookie added");
        }

        [HttpGet("get")]
        public IActionResult GetCookie()
        {
            if (Request.Cookies.TryGetValue(CookieName, out var cookieValue))
            {
                return Ok(cookieValue);
            }

            return NotFound("cookie doesnt exist");
        }

        [HttpDelete("delete")]
        public IActionResult DeleteCookie()
        {
            Response.Cookies.Delete(CookieName);
            return Ok("Cookie deleted");
        }

        [HttpGet("check-support")]
        public IActionResult CheckSupport()
        {
            const string testCookieName = "TestCookie";
            Response.Cookies.Append(testCookieName, "1", new CookieOptions
            {
                Expires = System.DateTime.Now.AddSeconds(10),
            });

            if (Request.Cookies.ContainsKey(CookieName))
            {
                Response.Cookies.Delete(testCookieName);
                return Ok("Cookies are supported");
            }
            return NotFound("Cookies are not supported");

        }
    }
}
