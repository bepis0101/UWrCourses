using Xunit;

namespace lista4
{
    public class ProcessSingleton
    {
        private static readonly Lazy<ProcessSingleton> _instance = new(() => new ProcessSingleton());

        public static ProcessSingleton Instance => _instance.Value;

        public Guid Id { get; } = Guid.NewGuid();

        private ProcessSingleton() { }
    }
    public class ThreadSingleton
    {
        [ThreadStatic]
        private static ThreadSingleton _instance;

        public static ThreadSingleton Instance => _instance ??= new ThreadSingleton();

        public Guid Id { get; } = Guid.NewGuid();

        private ThreadSingleton() { }
    }

    public class TimedSingleton
    {
        private static TimedSingleton _instance;
        private static DateTime _expiration = DateTime.MinValue;
        private static readonly object _lock = new();

        public Guid Id { get; } = Guid.NewGuid();

        private TimedSingleton() { }

        public static TimedSingleton Instance
        {
            get
            {
                lock (_lock)
                {
                    if (_instance == null || DateTime.UtcNow > _expiration)
                    {
                        _instance = new TimedSingleton();
                        _expiration = DateTime.UtcNow.AddSeconds(5);
                    }
                    return _instance;
                }
            }
        }
    }

    public class zad1
    {
        [Fact]
        public void ProcessSingleton_ShouldReturnSameInstance()
        {
            var instance1 = ProcessSingleton.Instance;
            var instance2 = ProcessSingleton.Instance;

            Assert.Equal(instance1.Id, instance2.Id);
        }

        [Fact]
        public void ThreadSingleton_ShouldReturnDifferentInstancesForDifferentThreads()
        {
            Guid id1 = ThreadSingleton.Instance.Id;
            Guid id2 = Guid.Empty;

            var thread = new Thread(() =>
            {
                id2 = ThreadSingleton.Instance.Id;
            });

            thread.Start();
            thread.Join();

            Assert.NotEqual(id1, id2);
        }

        [Fact]
        public void TimedSingleton_ShouldReturnSameInstanceWithin5Seconds()
        {
            var instance1 = TimedSingleton.Instance;
            Thread.Sleep(2000);
            var instance2 = TimedSingleton.Instance;

            Assert.Equal(instance1.Id, instance2.Id);
        }

        [Fact]
        public void TimedSingleton_ShouldReturnDifferentInstancesAfter5Seconds()
        {
            var instance1 = TimedSingleton.Instance;
            Thread.Sleep(6000); // >5s
            var instance2 = TimedSingleton.Instance;

            Assert.NotEqual(instance1.Id, instance2.Id);
        }


    }
}
