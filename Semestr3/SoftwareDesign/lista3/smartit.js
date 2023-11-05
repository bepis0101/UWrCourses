function* take(it, n) {
    for (let i = 0; i < n; i++) {
        yield it.next().value;
    }   
}

function* fibgen() {
    var a = 0, b = 1;
    while (true) {
        [a, b] = [b, a + b];
        yield a;
    }
}

for( let i of take(fibgen(), 10) ) {
    console.log(i);
}