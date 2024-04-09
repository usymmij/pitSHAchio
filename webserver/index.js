const express = require("express");
const path = require('path');
const bodyParser = require('body-parser');
const net = require('net')

const PORT = process.env.PORT || 3000;
const app = express();

app.use(express.static(path.resolve(__dirname, './client/build')))
app.use(bodyParser.text());

app.put('/api', (req, res) => {
  let hash = req.body;

  const socket = net.createConnection({ port: 3030 }, () => {
    console.log('connected')

    socket.on('data', (pws) => {
      console.log('response received');
      console.log(pws.toString())
      res.status(200).send(pws)
      socket.destroy();
    })
    socket.write(hash, () => {
      console.log('sent data');
    });
  });
  socket.on('error', (e) => {
    console.error(e)
    res.status(508).send()
  })

});

app.get("/", (req, res) => {
  console.log('dsad')
  res.sendFile(path.resolve(__dirname, './client/build', 'index.html'))
});


app.listen(PORT, () => {
  console.log(`Server listening on ${PORT}`);
});