var x = {
    a: 1,
    foo : function () {
        console.log(this.a);
    },
    set bar(i) { 
        this.a = i;
    },
    get bar() {
        return 5;
    },

};

// mozna uzyc Object.defineProperty dla metod i pol a dla get i set wrecz trzeba

console.log(x);
x.foo();
x.bar = 3;
console.log(x.bar);
x.foo();