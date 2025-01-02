using ChatApplication.Models;
using ChatApplication.Services;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;

namespace ChatApplication.Controllers
{
    public class AccountController : Controller
    {
        private readonly DbManager _context;
        private readonly IConfiguration _configuration;
        public AccountController(DbManager context, IConfiguration configuration)
        {
            _context = context;
            _configuration = configuration;
        }
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(AccountLoginModel model)
        {
            if(!this.ModelState.IsValid)
            {
                return View(model);
            }
            
            var user = await _context.Users.FirstOrDefaultAsync(u => u.Username == model.Username);
            
            if(user == null)
            {
                return View(model);
            }

            var password = await _context.Passwords.FirstOrDefaultAsync(p => p.UserId == user.Id);
            
            if(password == null)
            {
                return View(model);
            }

            if (!PasswordHandler.VerifyPassword(model.Password, password.PasswordHash))
            {
                return View(model);
            }


            var claims = new List<Claim>
            {
                new Claim(ClaimTypes.Name, user.Username),
                new Claim(ClaimTypes.Email, user.Email),
                new Claim(ClaimTypes.NameIdentifier, user.Id.ToString())
            };

            var identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
            var principal = new ClaimsPrincipal(identity);

            await HttpContext.SignInAsync(principal);

            return RedirectToAction("Index", "Chat");
        }

        public IActionResult Signup()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Signup(AccountSignupModel model)
        {
            if(!this.ModelState.IsValid)
            {
                return View(model);
            }
            
            var user = await _context.Users.FirstOrDefaultAsync(u => u.Username == model.Username);
            
            if(user != null)
            {
                return View(model);
            }

            if(model.Password != model.ConfirmPassword)
            {
                return View(model);
            }

            var newUser = new User()
            {
                Id = Guid.NewGuid(),
                Email = model.Email,
                Username = model.Username
            };

            var passwordHash = PasswordHandler.HashPassword(model.Password);

            var newPassword = new Password()
            {
                UserId = newUser.Id,
                PasswordHash = passwordHash
            };

            await _context.Users.AddAsync(newUser);
            await _context.Passwords.AddAsync(newPassword);
            await _context.SaveChangesAsync();

            return RedirectToAction("Login");
        }
        [HttpGet]
        public async Task<IActionResult> LogOut()
        {
            await this.HttpContext.SignOutAsync();
            return RedirectToAction("Index", "Home");
        }

    }

}
