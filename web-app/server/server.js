var express = require('express');
var app = express();
var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var Port = 8080;
var fileUpload = require('./fileUpload');
var compileIR = require('./compileIR');
var instrument = require('./instrument');
var profiling = require('./profiling');
var runtimeOptions = require('./runtimeOptions');
var faultInjection = require('./faultInjection');
var bodyParser = require('body-parser');

app.use(express.static(path.join(__dirname, '../views')));
app.use(bodyParser.json());

app.get('/', function(req, res){
	res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/uploadFile', function(req, res){
	fileUpload.processFileUpload(req,res);
});

app.post('/compileIR', function(req, res){
	compileIR.processCompileIR(req,res);
});

app.post('/instrument', function(req, res){
	instrument.processInstrument(req,res);
});

app.post('/profiling', function(req, res){
	profiling.processProfiling(req,res);
});

app.post('/runtimeOptions', function(req, res){
	runtimeOptions.processRuntimeOptions(req,res);
});

app.post('/faultInjection', function(req, res){
	faultInjection.processFaultInjection(req,res);
});

var server = app.listen(Port, function(){
	console.log('Server listening on port' + Port);
});
