const express = require('express');
const app = express();


app.use(express.static('public'));
app.set('view engine', 'ejs');
app.use(express.urlencoded({extended: true}));
app.use(express.json());

app.get('/', (req, res) => {
    res.render('form.ejs', errors = {})
});

app.post('/print', (req, res) => {
    const {name, surname, subject, tasks} = req.body;
    if(!name.length || !surname.length || !subject.length) {
        res.render('form.ejs', errors = {error: 'Wypełnij wszystkie wymagane pola pola'})
        console.log(errors)
        return;
    }

    const taskArr = Array.isArray(tasks) ? tasks.map(Number) : [Number(tasks)];
    console.log(taskArr)
    
    res.render('print.ejs', {name, surname, subject, taskArr});
});

app.get('/print', (req, res) => {
    res.render('print.ejs')
});
const port = 3000;
app.listen(port, () => console.log(`Server started at port http://localhost:${port}`));