```

BenchmarkDotNet v0.13.12, Windows 11 (10.0.22631.3296/23H2/2023Update/SunValley3)
13th Gen Intel Core i5-1340P, 1 CPU, 16 logical and 12 physical cores
.NET SDK 8.0.200
  [Host]   : .NET 8.0.3 (8.0.324.11423), X64 RyuJIT AVX2
  .NET 8.0 : .NET 8.0.3 (8.0.324.11423), X64 RyuJIT AVX2

Job=.NET 8.0  Runtime=.NET 8.0  

```
| Method | Mean      | Error     | StdDev    |
|------- |----------:|----------:|----------:|
| calc   | 0.0000 ns | 0.0000 ns | 0.0000 ns |
| _calc  | 4.4319 ns | 0.0971 ns | 0.0908 ns |
