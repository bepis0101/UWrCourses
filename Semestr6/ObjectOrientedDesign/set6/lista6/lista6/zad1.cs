using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista6
{
    public interface ILogger
    {
        void Log(string message);
    }
    public enum LogType { None, Console, File }
    public class ConsoleLogger : ILogger
    {
        public ConsoleLogger() { }
        public void Log(string message) 
        {
            Console.WriteLine(message);
        }
    }
    public class FileLogger : ILogger
    {
        private readonly string _filename;
        public FileLogger(string path) 
        {
            _filename = path;
        }
        public void Log(string message)
        {
            File.AppendAllText(_filename, message + Environment.NewLine);
        }
    }
    public class NullLogger : ILogger 
    {
        public void Log(string message) { }
    }

    public class LoggerFactory
    {
        private static readonly LoggerFactory _instance = new LoggerFactory();
        public static LoggerFactory Instance => _instance;
        private LoggerFactory() { }
        public ILogger GetLogger(LogType logType, string parameters = null)
        {
            return logType switch
            {
                LogType.None => new NullLogger(),
                LogType.Console => new ConsoleLogger(),
                LogType.File => new FileLogger(parameters),
                _ => new NullLogger(),
            };
        }
    }
}
