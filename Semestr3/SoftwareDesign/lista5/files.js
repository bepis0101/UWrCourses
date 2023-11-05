const fs = require('fs');
fs.readFile('./WEPPO/lista5/loremipsum.txt', 'utf8', (err, data) => {
    if (err) throw err;
    console.log(data);
});