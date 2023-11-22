import myObj from './exports.js'
const ins1 = new myObj();

import { Foo2 } from './exports.js'
const ins2 = new Foo2();

import { Foo2 as Bar } from './exports.js'
const ins3 = new Bar();


