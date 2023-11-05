function hasProperty(obj, propName) {
    return obj.hasOwnProperty(propName);
}

function enumerateOwnProperties(obj) {
    return Object.getOwnPropertyNames(obj);
}

function enumerateProperties(obj) {
    let props = [];
    for (let prop in obj) {
        props.push(prop);
    }
    return props;
}

var p = {
    name: 'jan'
}
var q = {
    surname: 'kowalski'
}
Object.setPrototypeOf( p, q );
console.log( p.name );
console.log( p.surname );

console.log(hasProperty(p, 'name')); // true
console.log(hasProperty(p, 'surname')); // false

console.log(enumerateOwnProperties(p)); // ['name']
console.log(enumerateProperties(p)); // ['name', 'surname']
