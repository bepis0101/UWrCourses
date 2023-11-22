let fib: Function = (n: number): number => {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

function memoize(fn: Function): Function {
    var cache = new Map();
    return function (n: number) {
        if( cache.has(n) ) {
            return cache.get(n);
        } else {
            var result = fn(n);
            cache.set(n, result);
            return result;
        }
    }
}

fib = memoize(fib);
for(let i = 0; i < 50; i++) {
    console.log(fib(i));
}
