var express = require('express');
var app = express();
var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var Port = 8080;
var fileUpload = require('./fileUpload');
var instrument = require('./instrument');
var bodyParser = require('body-parser');

var clientInfo = {};
app.use(express.static(path.join(__dirname, '../views')));
app.use(bodyParser.json());


app.get('/', function(req, res){
	res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/uploadFile', function(req, res){
	fileUpload.processFileUpload(req,res);
});

app.post('/instrument', function(req, res){
	instrument.processInstrument(req,res, clientInfo);
});

var server = app.listen(Port, function(){
	console.log('Server listening on port' + Port);
});
