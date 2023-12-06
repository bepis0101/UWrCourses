const express = require('express');
const router = express.Router();
const dropdownListRoute = require('./dropdownList');

router.get('/', (req, res) => {
  const selectedValue = 'Option 2';
  const options = ['Option 1', 'Option 2', 'Option 3'];
  res.render('mainView', { options, selectedValue });
});

router.use('/dropdownList', dropdownListRoute);

module.exports = router;
