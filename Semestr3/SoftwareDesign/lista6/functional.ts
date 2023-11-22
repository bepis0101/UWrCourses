function map<T>(f: (x: T) => T, list: T[]): T[] {
    for(let i = 0; i < list.length; i++) {
        list[i] = f(list[i]);
    }
    return list;
}

function filter<T>(f: (x: T) => boolean, list: T[]): T[] {
    let result: T[] = [];
    for(let i = 0; i < list.length; i++) {
        if(f(list[i])) {
            result.push(list[i]);
        }
    }
    return result;
}

function forEach<T>(f: (x: T) => any, list: T[]): any {
    for(let i = 0; i < list.length; i++) {
        f(list[i]);
    }
}

//tests
let list = [1, 2, 3, 4, 5];
console.log(map((x: number) => x * x, list));
console.log(filter((x: number) => x % 2 == 0, list));
forEach((x: number) => console.log(x), list);
