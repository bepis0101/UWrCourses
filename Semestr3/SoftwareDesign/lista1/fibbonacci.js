function fibbonacci(n) {
  if (n < 2) return n;
  return fibbonacci(n - 1) + fibbonacci(n - 2);
}

const fibbonacciIterative = (n) => {
    let a = 0, b = 1, c = 0;
    if (n < 2) return n;
    for (let i = 2; i <= n; i++) {
        [a,b] = [b, a+b];
    }
    return c;
};

console.time('fibbonacci');

for(let i = 10; i < 45; i++) {
  console.log(fibbonacci(i));
}

console.timeEnd('fibbonacci');

console.time('fibbonacciIterative');

for(let i = 10; i < 45; i++) {
  console.log(fibbonacciIterative(i));
}

console.timeEnd('fibbonacciIterative');
