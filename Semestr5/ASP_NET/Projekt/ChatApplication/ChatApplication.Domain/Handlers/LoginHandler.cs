using ChatApplication.Domain.Models;
using ChatApplication.Domain.Services;
using MediatR;

namespace ChatApplication.Domain.Handlers;

public class LoginUseCaseParameters : IRequest<LoginUseCaseResult>
{
    public string Username { get; set; }
    public string Password { get; set; }
}

public class LoginUseCaseResult
{
    public User? LoggedUser { get; set; } 
    public bool Success { get; set; }
    public string? ErrorMessage { get; set; }
}

public class LoginHandler : IRequestHandler<LoginUseCaseParameters, LoginUseCaseResult>
{
    private readonly DbManager _context;

    public LoginHandler(DbManager context)
    {
        _context = context;
    }

    public async Task<LoginUseCaseResult> Handle(LoginUseCaseParameters request, CancellationToken cancellationToken)
    {
        var user = await _context.GetUser(request.Username);

        if (user == null)
        {
            return new LoginUseCaseResult
            {
                ErrorMessage = "Incorrect username or password",
                Success = false
            };
        }

        var password = await _context.GetPassword(user.Id);

        if (password == null)
        {
            return new LoginUseCaseResult 
            {
                ErrorMessage = "Incorrect username or password",
                Success = false 
            };
        }

        var decision = PasswordHandler.VerifyPassword(request.Password, password.PasswordHash);
        if(decision == false)
        {
            return new LoginUseCaseResult
            {
                ErrorMessage = "Incorrect username or password",
                Success = false
            };
        }

        return new LoginUseCaseResult 
        { 
            Success = true,
            LoggedUser = user
        };
    }

}
