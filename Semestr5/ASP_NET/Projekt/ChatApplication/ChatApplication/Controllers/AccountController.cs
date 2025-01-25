using ChatApplication.Models;
using ChatApplication.Domain;
using MediatR;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Mvc;
using ChatApplication.Domain.Handlers;
using ChatApplication.Domain.Services;

namespace ChatApplication.Controllers
{
    public class AccountController : Controller
    {
        private IMediator _mediator;
        public AccountController(DbManager context, IMediator mediator)
        {
            _mediator = mediator;
        }
        public IActionResult Login()
        {
            var model = new AccountLoginModel()
            {
                Errors = new List<string>()
            };
            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> Login(AccountLoginModel model)
        {
            if(!this.ModelState.IsValid)
            {
                model.Errors.Add("Invalid input");
                return View(model);
            }
           
            var loginParameters = new LoginUseCaseParameters()
            {
                Username = model.Username,
                Password = model.Password
            };

            var result = await _mediator.Send(loginParameters);
            
            if(result.Success == false)
            {
                model.Errors.Add(result.ErrorMessage);
                return View(model);
            }

            var user = result.LoggedUser;
            
            var principal = PrincipalIssuer.IssuePrincipal(user);

            await HttpContext.SignInAsync(principal);

            return RedirectToAction("Index", "Chat");
        }

        public IActionResult Signup()
        {
            var model = new AccountSignupModel()
            {
                Errors = new List<string>()
            };
            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> Signup(AccountSignupModel model)
        {
            if(!this.ModelState.IsValid)
            {
                return View(model);
            }
            
            var signUpParameters = new SignUpUseCaseParameters()
            {
                Username = model.Username,
                Password = model.Password,
                ConfirmPassword = model.ConfirmPassword,
                Email = model.Email
            };
            var result = await _mediator.Send(signUpParameters);

            if(result.Success == false)
            {
                model.Errors.Add(result.ErrorMessage);
                return View(model);
            }
            

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
