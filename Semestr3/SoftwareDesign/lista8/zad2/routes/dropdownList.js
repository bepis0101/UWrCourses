// routes/dropdownList.js
const express = require('express');
const router = express.Router();

router.get('/:selectedValue?', (req, res) => {
  res.render('dropdownList', { options, selectedValue });
});

module.exports = router;
