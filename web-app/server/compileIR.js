var fs = require('fs');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processCompileIR = function (req, res) {

	var fileName = req.body.fileName;

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var generateMakeCmd = LLFI_BUILD_ROOT + "tools/GenerateMakefile --readable --all -o " + fileName + ".ll";


	var commands = [cdDirCmd + " && " + generateMakeCmd, cdDirCmd + " && " + "make"];

	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				console.log(results);
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		// all done here, all results in the results array
		console.log("CompileIR success");

	}, function(err) {
		// error here
	}).then(function() {

		var files = [];
		// Send the .ll file and make file back to front-end
		fs.readFile("./uploads/"+ req.ip+"/" + fileName + ".ll", 'utf8', function(err, data) {
			var fileObj = {};
			fileObj.fileName = fileName + ".ll";
			fileObj.fileContent = data;
			files.push(fileObj);
			if (err) console.log("err in file reading, ", err);
			fs.readFile("./uploads/"+ req.ip+"/Makefile", 'utf8', function(err, data) {
				var fileObj = {};
				fileObj.fileName = "Makefile";
				fileObj.fileContent = data;
				files.push(fileObj);
				if (err) console.log("err in file reading, ", err);
				res.send(files);
			});
		});
	});
}

var execPromise = function(cmd) {
	console.log("exec");
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			console.log("stdout" + stdout);
			if (err) return reject(err);
			resolve(stdout);
		});
	});
}
