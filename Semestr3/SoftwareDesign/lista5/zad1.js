const module1 = require('./modules.js');
const Tree = module1;
const tree = new Tree(1, new Tree(2, new Tree(4), new Tree(5)), new Tree(3));
for (var e of tree) {
    console.log(e);
}

let a = require('./a');
a.work_a(5);