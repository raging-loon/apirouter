const express = require('express')

const app = express()


app.post('/test', (req, res) => {
    res.send('hello')
})

app.listen(80, () => { console.log("listening...") })