var Person = function (name, surname) {
    this.name = name;
    this.surname = surname;
}
Person.prototype.say = () => {
    return `${this.name} ${this.surname}`;
}

var Worker = function (name, surname, age) {
    Person.call(this, name, surname);
    this.age = age;
}

// Worker.prototype = Person.prototype;
// console.log(Worker.prototype.constructor); // Person

// var w = new Worker('Jan', 'Kowalski', 32);
// console.log(w.say()); // undefined undefined

Worker.prototype = new Person();

Worker.prototype.say = () => {
    return `${this.name} ${this.surname} ${this.age}`;
}
console.log(Worker.prototype.constructor); // Person

var w = new Worker('Jan', 'Kowalski', 32);
console.log(w.say());  // undefined undefined underfined

