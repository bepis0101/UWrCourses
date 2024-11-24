using Microsoft.AspNetCore.Html;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations;
using System.Linq.Expressions;

namespace LoginVariants.Models
{
    public class LoginModel
    {
        public string Username { get; set; }
        public string Password { get; set; }
        [PeselAttribute]
        public string Pesel { get; set; }
    }
    public static class CustomHtmlHelpers
    {
        public static IHtmlContent Login(this IHtmlHelper helper, string username, object? usernameVal, string password, object? passwordVal)
        {
            var unInput = new TagBuilder("input");

            unInput.Attributes.Add("type", "text");
            unInput.Attributes.Add("name", username);
            if (usernameVal != null)
            {
                unInput.MergeAttribute("value", usernameVal.ToString());
            }


            var pwInput = new TagBuilder("input");

            pwInput.Attributes.Add("type", "password");
            pwInput.Attributes.Add("name", password);
            if (passwordVal != null)
            {
                pwInput.MergeAttribute("value", passwordVal.ToString());
            }

            var label = new TagBuilder("label");
            label.InnerHtml.Append("Username");
            label.Attributes.Add("for", username);
            var label2 = new TagBuilder("label");
            label2.InnerHtml.Append("Password");
            label2.Attributes.Add("for", password);


            var content = new HtmlContentBuilder()
                .AppendHtml(label)
                .AppendHtml(unInput)
                .AppendHtml(label2)
                .AppendHtml(pwInput);
            return content;
        }
        public static IHtmlContent LoginFor<TModel, TProperty>(this IHtmlHelper<TModel> helper,
                                                            Expression<Func<TModel, TProperty>> usernameProperty,
                                                            Expression<Func<TModel, TProperty>> passwordProperty)
        {
            var unInput = new TagBuilder("input");
            unInput.Attributes.Add("type", "text");
            unInput.Attributes.Add("name", helper.NameFor(usernameProperty).ToString());
            if (usernameProperty != null)
            {
                //unInput.MergeAttribute("value", );
            }

            var pwInput = new TagBuilder("input");
            pwInput.Attributes.Add("type", "password");
            pwInput.Attributes.Add("name", helper.NameFor(passwordProperty).ToString());
            if (passwordProperty != null)
            {
                //pwInput.MergeAttribute("value", );
            }
            var label = new TagBuilder("label");
            label.InnerHtml.Append("Username");
            label.Attributes.Add("for", helper.NameFor(usernameProperty).ToString());
            var label2 = new TagBuilder("label");
            label2.InnerHtml.Append("Password");
            label2.Attributes.Add("for", helper.NameFor(passwordProperty).ToString());

            var content = new HtmlContentBuilder()
                .AppendHtml(label)
                .AppendHtml(unInput)
                .AppendHtml(label2)
                .AppendHtml(pwInput);
            return content;
        }
    }
    public class PeselAttribute : ValidationAttribute
    {
        protected override ValidationResult? IsValid(object? value, ValidationContext validationContext)
        {
            string? pesel = value as string;
            if (String.IsNullOrEmpty(pesel) || pesel.Length != 11 || !pesel.All(char.IsAsciiDigit))
            {
                return new ValidationResult("incorrect pesel");
            }
            int[] weights = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3 };
            int sum = 0;
            for (int i = 0; i < 10; i++)
            {
                sum += weights[i] * (pesel[i] - '0');
            }
            int control = (10 - sum % 10) % 10;

            if (control != pesel[10] - '0')
            {
                return new ValidationResult("incorrect pesel");
            }
            return ValidationResult.Success;
        }

    }
}
