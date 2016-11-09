var fs = require('fs');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";
var execPromise = require('./utils/execPromise').execPromise;

exports.processCompileIR = function (req, res) {

	var fileName = req.body.fileName;

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var generateMakeCmd = LLFI_BUILD_ROOT + "tools/GenerateMakefile --readable --all -o " + fileName + ".ll";


	var commands = [cdDirCmd + " && " + generateMakeCmd, cdDirCmd + " && " + "make"];

	var consoleLog = [];
	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				if (stdout) results.push(stdout);
				consoleLog = results;
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		// all done here, all results in the results array

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
				var response = {files: files, consoleLog: consoleLog};
				console.log("CompileIR success");
				res.send(response);
			});
		});
	});
}

// var execPromise = function(cmd) {
// 	return new Promise(function(resolve, reject) {
// 		exec(cmd, function(err, stdout) {
// 			if (err) return reject(err);
// 			resolve(cmd + stdout);
// 		});
// 	});
// }