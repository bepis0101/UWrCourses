using ChatApplication.Domain.Models;
using Microsoft.AspNetCore.Authentication.Cookies;
using System.Security.Claims;

namespace ChatApplication.Domain.Services
{
    public static class PrincipalIssuer
    {
        public static ClaimsPrincipal IssuePrincipal(User user)
        {
            var claims = new List<Claim>
            {
                new Claim(ClaimTypes.Name, user.Username),
                new Claim(ClaimTypes.Email, user.Email),
                new Claim(ClaimTypes.NameIdentifier, user.Id.ToString())
            };

            var identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
            var principal = new ClaimsPrincipal(identity);
            return principal;

        }
    }
}
