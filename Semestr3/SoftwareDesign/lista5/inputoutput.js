const stdin = process.stdin;
process.stdout.write('What is your name?\n');
let yourName = '';
stdin.addListener('data', (data) => {
    yourName += data.toString();
    console.log(`Hello ${yourName}`);
    stdin.pause();
});
