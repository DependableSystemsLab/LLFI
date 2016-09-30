var express = require('express');
var app = express();
var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var Port = 8080;
app.use(express.static(path.join(__dirname, '../views')));

app.get('/', function(req, res){
	res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/upload', function(req, res){

	// create an incoming form object
	var form = new formidable.IncomingForm();

	// specify that we want to allow the user to upload multiple files in a single request
	form.multiples = true;

	// store all uploads in the /uploads directory
	form.uploadDir = path.join(__dirname, '/uploads');

	// every time a file has been uploaded successfully,
	// rename it to it's orignal name
	form.on('file', function(field, file) {
	 fs.rename(file.path, path.join(form.uploadDir, file.name));
	});
	console.log(1);

	// log any errors that occur
	form.on('error', function(err) {
		console.log('An error has occured: \n' + err);
	});

	// once all the files have been uploaded, send a response to the client
	form.on('end', function() {
		res.end('success');
	});

	// parse the incoming request containing the form data
	form.parse(req);

});

var server = app.listen(Port, function(){
	console.log('Server listening on port' + Port);
});
