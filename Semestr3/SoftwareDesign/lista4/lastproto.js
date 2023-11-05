function getLastPrototype(obj) {
    var p = obj;
    do {
        obj = p;
        p = Object.getPrototypeOf(obj);
    } while(p);

    return obj;
}

const obj1 = {};
const obj2 = {};
const obj3 = {};

Object.setPrototypeOf(obj2, obj1);
Object.setPrototypeOf(obj3, obj2);

console.log(getLastPrototype(obj3) === getLastPrototype(obj1) && getLastPrototype(obj2) == getLastPrototype(obj1)); // true