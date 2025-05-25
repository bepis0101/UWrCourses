using System.Linq.Expressions;

namespace lista6
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ILogger logger1 = LoggerFactory.Instance.GetLogger(LogType.Console);
            logger1.Log("foo bar"); // logowanie na konsole

            ILogger logger2 = LoggerFactory.Instance.GetLogger(LogType.None);
            logger2.Log("qux"); // brak logowania

            var context = new Context();
            context.SetValue("x", true);
            context.SetValue("y", false);
            context.SetValue("z", false);
            // (T || y) && (x || z) === T
            Console.WriteLine(new BinaryExpression(
                                  new BinaryExpression(
                                      new ConstExpression(true), new UnaryExpression("y"), BinaryOperator.Or),
                                  new BinaryExpression(
                                      new UnaryExpression("x"), new UnaryExpression("z"), BinaryOperator.Or),
                                  BinaryOperator.And).Interpret(context));


            Tree root = new TreeNode()
            {
                Left = new TreeNode()
                {
                    Left = new TreeLeaf(),
                    Right = new TreeLeaf()
                },
                Right = new TreeLeaf()
            };

            DepthVisitor depthVisitor = new DepthVisitor();
            int depth = depthVisitor.Visit(root);

            Console.WriteLine($"Głębokość drzewa: {depth}"); // powinno wypisać: 3

            Func<int, int> expr0 = x => -x;
            Expression<Func<int, int>> expr1 = x => -x;
            Expression<Func<int>> expr2 = () => 42;
            Expression<Func<int, bool>> expr3 = x => x > 0;

            var visitor = new PrintExpressionVisitor();

            Console.WriteLine("== Wyrażenie unarne ==");
            visitor.Visit(expr1);

            Console.WriteLine("\n== Wyrażenie stałe ==");
            visitor.Visit(expr2);

            Console.WriteLine("\n== Wyrażenie binarne z parametrem ==");
            visitor.Visit(expr3);
        }
    }
}
