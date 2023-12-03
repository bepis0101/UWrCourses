const express = require('express');
const app = express();
const cookieParser = require('cookie-parser');

app.set('view engine', 'ejs');
app.use(cookieParser());
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    var cookie;
    if(!req.cookies.cookie) {
        cookie = new Date().getTime().toString();
        res.cookie('cookie', cookie, { maxAge: 1000 * 60 * 60 * 24 * 365 });
    } else {
        cookie = req.cookies.cookie;
    }
    res.render('index.ejs', { cookie: cookie })
});

app.post('/', (req, res) => {
    res.clearCookie('cookie');
    res.redirect('/deleted');
});

app.get('/deleted', (req, res) => {
    if(!req.cookies.cookie) {
        res.redirect('/');
    }
    res.render('deleted.ejs');
});

const port = 3300;

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
});