using System;
using System.Collections.Concurrent;
using System.Threading;
namespace lista8
{
    public interface ICommand
    {
        void Execute();
    }
    public class FileReceiver
    {
        public void DownloadFtp(string fileName)
        {
            Console.WriteLine($"Pobieranie pliku przez FTP: {fileName}");
        }

        public void DownloadHttp(string fileName)
        {
            Console.WriteLine($"Pobieranie pliku przez HTTP: {fileName}");
        }

        public void CreateRandomFile(string fileName)
        {
            var rnd = new Random();
            var data = new byte[100];
            rnd.NextBytes(data);
            File.WriteAllBytes(fileName, data);
            Console.WriteLine($"Utworzono losowy plik: {fileName}");
        }

        public void CopyFile(string sourcePath, string destPath)
        {
            File.Copy(sourcePath, destPath, overwrite: true);
            Console.WriteLine($"Skopiowano plik z {sourcePath} do {destPath}");
        }
    }
    public class FtpDownloadCommand : ICommand
    {
        private readonly FileReceiver _receiver;
        private readonly string _fileName;

        public FtpDownloadCommand(FileReceiver receiver, string fileName)
        {
            _receiver = receiver;
            _fileName = fileName;
        }

        public void Execute() => _receiver.DownloadFtp(_fileName);
    }

    public class HttpDownloadCommand : ICommand
    {
        private readonly FileReceiver _receiver;
        private readonly string _fileName;

        public HttpDownloadCommand(FileReceiver receiver, string fileName)
        {
            _receiver = receiver;
            _fileName = fileName;
        }

        public void Execute() => _receiver.DownloadHttp(_fileName);
    }

    public class CreateRandomFileCommand : ICommand
    {
        private readonly FileReceiver _receiver;
        private readonly string _fileName;

        public CreateRandomFileCommand(FileReceiver receiver, string fileName)
        {
            _receiver = receiver;
            _fileName = fileName;
        }

        public void Execute() => _receiver.CreateRandomFile(_fileName);
    }

    public class CopyFileCommand : ICommand
    {
        private readonly FileReceiver _receiver;
        private readonly string _source;
        private readonly string _destination;

        public CopyFileCommand(FileReceiver receiver, string source, string destination)
        {
            _receiver = receiver;
            _source = source;
            _destination = destination;
        }

        public void Execute() => _receiver.CopyFile(_source, _destination);
    }
    

    public class CommandQueue
    {
        private readonly BlockingCollection<ICommand> _queue = new();

        public void EnqueueCommand(ICommand command)
        {
            _queue.Add(command);
        }

        public void StartWorker()
        {
            Task.Run(() =>
            {
                foreach (var command in _queue.GetConsumingEnumerable())
                {
                    command.Execute();
                }
            });
        }
        public void Stop()
        {
            _queue.CompleteAdding();
        }
    }

}
