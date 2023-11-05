const http = require('http');

var req = http.request('http://www.google.com', (res) => {
    var data = '';
    res.on('data', (chunk) => {
        data += chunk;
    });
    res.on('end', () => {
        console.log(data);
    });
});
req.on('error', (err) => {
    console.log(err);
});
req.end();

function getContent(url) {
    return new Promise((resolve, reject) => {
        var req = http.get(url, (res) => {
            var data = '';
            res.on('data', (chunk) => {
                data += chunk;
            });
            res.on('end', () => {
                resolve(data);
            });
        });
        req.on('error', (err) => {
            reject(err);
        });
    });
}