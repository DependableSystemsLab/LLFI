var path = require('path');
var formidable = require('formidable');
var fs = require('fs');
var Port = 8080;
var exec = require('child_process').exec;

var clientInfo ={};

exports.processFileUpload = function (req, res) {
	// create an incoming form object
	var form = new formidable.IncomingForm();

	var clientIP = req.ip;
	// specify that we want to allow the user to upload multiple files in a single request
	form.multiples = false;


	// The dir name for each client
	var dirName = "./uploads/" + clientIP + "/";

	exec("rm -rf " + dirName + "*", function(err, stdout) {
		if (err) console.log("err in clearing dir", dirName, err);
	});

	// store all uploads in the /uploads directory
	form.uploadDir = path.join(__dirname, dirName);
	// Make a dir to store the files from a client
	if (!fs.existsSync(dirName)) {
		fs.mkdirSync(dirName);
	}
	// every time a file has been uploaded successfully,
	// rename it to it's orignal name
	form.on('file', function(field, file) {
		this.fileName = file.name;
		fs.rename(file.path, path.join(form.uploadDir, file.name), function (err) {
			if (err) {
				console.log("An error has occured in file rename, ", err);
			}
			else {
				clientInfo.fileName = file.name;
				fs.readFile(dirName + file.name, 'utf8', function(err, data) {
					var fileObj = {};
					fileObj.fileName = file.name;
					fileObj.fileContent = data;
					if (err) console.log("err in file reading, ", err);
					res.send(fileObj);
				});
			}
		});
	}.bind(this));

	// log any errors that occur
	form.on('error', function(err) {
		console.log('An error has occured: \n' + err);
	});

	// once all the files have been uploaded, send a response to the client
	form.on('end', function() {
		// res.end("success");
	});
	// parse the incoming request containing the form data
	form.parse(req);
}