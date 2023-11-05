function fibiter() {
    var a = 0, b = 1;
    return {
        next: function () {
            [a, b] = [b, a + b];
            return {
                value: a,
                done: false,
            }
        }
    }
}

function* fibgen() {
    var a = 0, b = 1;
    while (true) {
        [a, b] = [b, a + b];
        yield a;
    }
}

var it = fibiter();

for( var res; res = it.next(), !res.done; ) {
    console.log(res.value);
}

it = fibgen();

for( var res; res = it.next(), !res.done; ) {
    console.log(res.value);
}