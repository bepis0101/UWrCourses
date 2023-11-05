function memoize(fn) {
    var cache = {};
    return function(n) {
        if ( n in cache ) {
        return cache[n];
        } else {
            var result = fn(n);
            cache[n] = result;
            return result;
        }
    }
}
   

function fibbonacci(n) {
    if (n < 2) return n;
    return fibbonacci(n - 1) + fibbonacci(n - 2);
}

const fibbonacciIterative = (n) => {
    let a = 0, b = 1, c = 0;
    if (n < 2) return n;
    for (let i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
};

fibbonacci = memoize(fibbonacci);
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
