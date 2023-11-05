const person = {
    name: 'John',
    surnname: 'Doe',
}

const string = {};

person['mega'] = 'mega';
person[string] = string;

// console.log(person['mega']);
// console.log(person[string]);

var tab = [1, 2, 3, 4, 5];
var p = {
    valueOf: function () {
        return 3;
    }
}
tab[p] = 7;

p[7] = 1;
// console.log(p['7']);
// console.log(tab);
// console.log(tab[p]);

// 1. po . mozna uzywac zmiennych po [] tylko stringi
// 2. dla liczby undefined
//    dla objektu underfined
//    obiekt jest zamieniany na stringa '[object Object]'

var tab2 = [1, 2, 3, 4, 5];
// console.log(tab2.length);
// tab2.length = 3;
// console.log(tab2);
// tab2.length = 7;
// console.log(tab2);

tab2.oooo = 1;

var p = {};
var q = {
    toString: function () {
        return 2;
    }
}
console.log(tab2[q]);

// 3. dla napisu undefined (chyba ze napis jest liczba wtedy proba konwersji)
//    dla objektu undefined (nawet jak ma  valueOf)
//    daje mozliwosc odwolania sie 
//    dla zmniejszenia length usuwa elementy z konca
//    dla zwiekszenia length dodaje empty items