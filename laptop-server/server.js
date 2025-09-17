const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));

let lastUpload = {};

app.post('/upload', (req, res) => {
  lastUpload = req.body;
  console.log("Received data:", lastUpload);
  res.status(200).send('Received');
});

app.get('/latest', (req, res) => {
  res.json(lastUpload);
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
