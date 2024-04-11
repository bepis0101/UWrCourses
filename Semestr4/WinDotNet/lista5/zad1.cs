using System;
using BenchmarkDotNet;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Jobs;
using BenchmarkDotNet.Running;



public class _Benchmark

{
    private int a = 1;
    private int b = 2;
    private dynamic c;
    private dynamic d;
    [GlobalSetup]
    public void Setup()
    {
        c = a;
        d = b;
    }
    [Benchmark]
    public int calc()
    {
        return a + b;
    }
    [Benchmark]
    public dynamic _calc()
    {
        return c + d;
    }

    [Benchmark]
    [Arguments(1, 6)]
    [Arguments(1, 6)]
    [Arguments(1, 6)]
    public void Foo(int x, int y)
    {

    }
    [Benchmark]
    [ArgumentsSource("Foo2Source")]
    public void Foo2(int x, int y)
    {

    }

    public IEnumerable<object[]> Foo2Source()
    {
        yield return new object[] { 1, 2 };
        yield return new object[] { 3, 4 };
    }
}
public class Task1
{
    public static void Main(string[] args)
    {
        var summary = BenchmarkRunner.Run<_Benchmark>();
    }

}