const readline = require('readline');
const fs = require('fs');


async function processByLine() {
    const fileStream = fs.createReadStream('./logs.txt');
    const rl = readline.createInterface({
        input: fileStream,
        crlfDelay: Infinity
    });
    // save to array lines
    var lines = [];
    for await (const line of rl) {
        lines.push(line);
    }
    // save to array logs
    var logs = [];
    for (var i = 0; i < lines.length; i++) {
        logs.push(lines[i].split(' '));
    }
    var dict = {};
    for (var i = 0; i < logs.length; i++) {
        if (dict[logs[i][2]] == undefined) {
            dict[logs[i][2]] = 1;
        } else {
            dict[logs[i][2]]++;
        }
    }

    var elements = Object.keys(dict).map(function(key) {
        return [key, dict[key]];
    });
    elements.sort(function(first, second) {
        return second[1] - first[1];
    });

    for(let i = 0; i < 3; i++) {
        console.log(elements[i]);
    }
    return elements;
}

async function main(){
    var res = await processByLine();
    console.log(res);
}

main();