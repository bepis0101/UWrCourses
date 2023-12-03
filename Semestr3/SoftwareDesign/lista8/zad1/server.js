const express = require('express');
const app = express();
const multer = require('multer');
const upload = multer({dest: 'uploads/'});


app.use(express.static('public'));
app.set('view engine', 'ejs');
app.use(express.urlencoded({extended: true}));
app.use(express.json());
app.set('views', './views');


const port = 3000;


app.listen(port, () => {
    console.log('Server listening on port ' + port);
});

app.get('/', (req, res) => {
    res.render('main.ejs');
});

app.post('/', upload.single('file1'), (req, res) => {
    req.file ? res.send('File uploaded!') : res.send('No file uploaded!');
});