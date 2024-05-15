using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace lista9
{
    internal class Task2
    {
        static Semaphore agentSem = new Semaphore(1, 1);
        static Semaphore tobaccoSem = new Semaphore(0, 1);
        static Semaphore paperSem = new Semaphore(0, 1);
        static Semaphore matchSem = new Semaphore(0, 1);

        static void AgentA()
        {
            while (true)
            {
                agentSem.WaitOne();
                Thread.Sleep(1000);
                Random rnd = new Random();
                int choice = rnd.Next(0, 3);
                switch (choice)
                {
                    case 0:
                        Console.WriteLine("Agent A puts tobacco and paper on the table");
                        tobaccoSem.Release();
                        paperSem.Release();
                        break;
                    case 1:
                        Console.WriteLine("Agent A puts tobacco and matches on the table");
                        tobaccoSem.Release();
                        matchSem.Release();
                        break;
                    case 2:
                        Console.WriteLine("Agent A puts paper and matches on the table");
                        paperSem.Release();
                        matchSem.Release();
                        break;
                }
            }
        }

        static void SmokerTobacco()
        {
            while (true)
            {
                tobaccoSem.WaitOne();
                paperSem.WaitOne();
                Console.WriteLine("Smoker with tobacco picks up paper and matches and smokes");
                Thread.Sleep(1000);
                Console.WriteLine("Smoker with tobacco is done smoking");
                agentSem.Release();
            }
        }

        static void SmokerPaper()
        {
            while (true)
            {
                tobaccoSem.WaitOne();
                matchSem.WaitOne();
                Console.WriteLine("Smoker with paper picks up tobacco and matches and smokes");
                Thread.Sleep(1000);
                Console.WriteLine("Smoker with paper is done smoking");
                agentSem.Release();
            }
        }

        static void SmokerMatch()
        {
            while (true)
            {
                paperSem.WaitOne();
                matchSem.WaitOne();
                Console.WriteLine("Smoker with match picks up tobacco and paper and smokes");
                Thread.Sleep(1000);
                Console.WriteLine("Smoker with match is done smoking");
                agentSem.Release();
            }
        }
        public static void Main2()
        {
            Thread agentA = new Thread(AgentA);
            Thread smokerTobacco = new Thread(SmokerTobacco);
            Thread smokerPaper = new Thread(SmokerPaper);
            Thread smokerMatch = new Thread(SmokerMatch);

            agentA.Start();
            smokerTobacco.Start();
            smokerPaper.Start();
            smokerMatch.Start();

            agentA.Join();
            smokerTobacco.Join();
            smokerPaper.Join();
            smokerMatch.Join();
        }
    }
}
