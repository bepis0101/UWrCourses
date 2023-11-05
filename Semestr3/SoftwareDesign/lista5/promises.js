const fs = require('fs').promises;
const { readFile } = require('fs');
const util = require('util');

const readFileAsync1 = util.promisify(fs.readFile);

function readFileAsync(path, encoding) {
    return new Promise((resolve, reject) => {
        fs.readFile(path, encoding, (err, data) => {
            if (err) {
                reject(err);
            }
            resolve(data);
        });
    });
}

// readFile(path, encoding)
//     .then((data) => {
//         console.log(data);
//     })
//     .catch((err) => {
//         console.log(err);
//     });

//      fs.readFile(path, encoding)
//         .then((data) => {
    //         console.log(data);
    //     })
    //     .catch((err) => {
    //         console.log(err);
    //     });

async function main() {
    try {
        const data = await readFileAsync(path, encoding);
        console.log(data);
    } catch(err) {
        console.log(err);
    }
}