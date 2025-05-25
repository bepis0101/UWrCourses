namespace lista8
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var classifier = new ClassifierHandler();
            classifier.SetNext(new PraiseHandler())
                      .SetNext(new ComplaintHandler())
                      .SetNext(new OrderHandler())
                      .SetNext(new OtherHandler())
                      .SetNext(new InvalidMessageHandler())
                      .SetNext(new ArchiveHandler());

            // Przykładowe wiadomości
            var email = new Message("Dziękujemy!", "Chcemy podziękować za pomoc.");
            var request = new Request(email);
            classifier.Handle(request);
            email = new Message("Skarga", "CHciałbym złożyć skargę");
            request = new Request(email);
            classifier.Handle(request);

            var receiver = new FileReceiver();
            var queue = new CommandQueue();

            // Uruchomienie dwóch pracowników
            queue.StartWorker();
            queue.StartWorker();

            // Producent: dodaje polecenia
            queue.EnqueueCommand(new FtpDownloadCommand(receiver, "plik1.txt"));
            queue.EnqueueCommand(new HttpDownloadCommand(receiver, "plik2.txt"));
            queue.EnqueueCommand(new CreateRandomFileCommand(receiver, "losowy.txt"));
            queue.EnqueueCommand(new CopyFileCommand(receiver, "losowy.txt", "kopialosowy.txt"));

            Thread.Sleep(2000);  // czekamy chwilę na przetworzenie
            queue.Stop();
        }
    }
}
