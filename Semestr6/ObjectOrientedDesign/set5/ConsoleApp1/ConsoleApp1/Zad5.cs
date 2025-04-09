using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public interface IService
    {
        string GetData(int id);
    }

    public class RealService : IService
    {
        private static Random _rnd = new Random();

        public string GetData(int id)
        {
            if (_rnd.NextDouble() < 0.5)
                throw new Exception("Simulated failure");

            return $"Data for ID: {id}";
        }
    }

    public class RetryProxy : IService
    {
        private readonly IService _realService;
        private readonly int _maxRetries;

        public RetryProxy(IService realService, int maxRetries = 3)
        {
            _realService = realService;
            _maxRetries = maxRetries;
        }

        public string GetData(int id)
        {
            int attempt = 0;
            while (true)
            {
                try
                {
                    return _realService.GetData(id);
                }
                catch (Exception ex)
                {
                    attempt++;
                    Console.WriteLine($"[RetryProxy] Attempt {attempt} failed: {ex.Message}");
                    if (attempt >= _maxRetries)
                        throw;
                }
            }
        }
    }

    public class LoggingProxy : IService
    {
        private readonly IService _inner;

        public LoggingProxy(IService inner)
        {
            _inner = inner;
        }

        public string GetData(int id)
        {
            Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Calling GetData({id})");
            try
            {
                string result = _inner.GetData(id);
                Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Result = {result}");
                return result;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Exception = {ex.Message}");
                throw;
            }
        }
    }

    public static class ServiceFactory
    {
        public static IService CreateService()
        {
            // Kolejność: RealService → Retry → Logging
            IService real = new RealService();
            IService withRetry = new RetryProxy(real, maxRetries: 3);
            IService withLogging = new LoggingProxy(withRetry);
            return withLogging;
        }
    }


}
