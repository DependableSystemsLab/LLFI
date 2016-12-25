var express = require('express');
var app = express();
var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var http = require('http');

var Port = 8080;
var fileUpload = require('./fileUpload');
var compileToIR = require('./compileToIR');
var preInstrument = require('./preInstrument');
var instrument = require('./instrument');
var profiling = require('./profiling');
var runtimeOptions = require('./runtimeOptions');
var faultInjection = require('./faultInjection');
var traceGraph = require('./traceGraph');
var bodyParser = require('body-parser');

app.use(express.static(path.join(__dirname, '../views')));
app.use(bodyParser.json());

app.get('/', function(req, res){
	try {
		res.sendFile(path.join(__dirname, 'index.html'));
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/uploadFile', function(req, res){
	try {
		fileUpload.processFileUpload(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/compileToIR', function(req, res){
	try {
		compileToIR.processCompileToIR(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/preInstrument', function(req, res){
	try {
		preInstrument.processPreInstrument(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/instrument', function(req, res){
	try {
		instrument.processInstrument(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/profiling', function(req, res){
	try {
		profiling.processProfiling(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/runtimeOptions', function(req, res){
	try {
		runtimeOptions.processRuntimeOptions(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/faultInjection', function(req, res){
	try {
		faultInjection.processFaultInjection(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.post('/traceGraph', function(req, res){
	try {
		traceGraph.processTrace(req,res);
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

app.get('/tracepdf', function(req, res){
	try {
		res.download("./uploads/" + req.ip +"/llfi/trace_report_output/TraceGraph.pdf");
		console.log('Trace graph sent');
	} catch (err) {
		res.status(500);
		res.send(err);
	}
});

var server = app.listen(Port, function(){
	console.log('Server listening on port' + Port);
});
