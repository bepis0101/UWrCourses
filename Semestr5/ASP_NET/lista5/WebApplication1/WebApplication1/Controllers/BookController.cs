using Microsoft.AspNetCore.Mvc;
using WebApplication1.Data;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    public class BookController : Controller
    {
        private IDataRepository _dataRepository;

        public BookController(IDataRepository dataRepository)
        {
            _dataRepository = dataRepository;
        }
        public async Task<IActionResult> Index()
        {
            var books = await _dataRepository.GetAll();
            return View(books);
        }

        [HttpGet]
        public IActionResult Add()
        {
            return View();
        }
        [HttpPost]
        public IActionResult Add(BookModel book)
        {
            if(ModelState.IsValid)
            {
                Guid guid = Guid.NewGuid();
                _dataRepository.Add(guid, book.Title, book.Author, book.ISBN, book.YearOfRelease);
                return RedirectToAction("Index");
            }
            else
            {
                return View(book);
            }
        }

    }
}
