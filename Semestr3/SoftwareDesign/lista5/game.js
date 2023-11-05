const { randomInt } = require('crypto');
const readline = require('readline');
var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

let num = randomInt(0, 100);
var game = function (q) {
    return new Promise((resolve, reject) => {
        rl.question(q, (answer) => {
            resolve(answer);
        });
    });
}

async function main() {
    var answer;
    while(true) {
        answer = await game("Guess a number: ");
        if (answer == num) {
            console.log("You win!");
            rl.close();
            break;
        } else if (answer > num) {
            console.log("Too high!");
        } else {
            console.log("Too low!");
        }
    }
}
main();