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
        public async Task<IActionResult> Add(BookModel book)
        {
            if(ModelState.IsValid)
            {
                Guid guid = Guid.NewGuid();
                book.ID = guid;
                await _dataRepository.Add(book);
                return RedirectToAction("Index");
            }
            else
            {
                return View(book);
            }
        }
        [HttpGet]
        public async Task<IActionResult> Edit(Guid id)
        {
            var model = await _dataRepository.Get(id);
            if( model != null )
            {
                return View(model);
            }
            return View(new BookModel());
        }
        [HttpPost]
        public async Task<IActionResult> Edit(BookModel model)
        {
            if (ModelState.IsValid)
            {
                await _dataRepository.Update(model);
                return RedirectToAction("Index");
            }
            else
            {
                return View(model);
            }
        }
        [HttpGet]
        public async Task<IActionResult> Delete(Guid id)
        {
            var model = await _dataRepository.Get(id);
            if (model != null)
            {
                return View(model);
            }
            return View(new BookModel());
        }
        [HttpPost]
        public async Task<IActionResult> Delete(BookModel model)
        {
            await _dataRepository.Delete(model.ID);
            return RedirectToAction("Index");
        }


    }
}
