const express = require("express");

const PORT = process.env.PORT || 6000;

const app = express();

app.get("/", (req, res) => {
  
});

app.listen(PORT, () => {
  console.log(`Server listening on ${PORT}`);
});