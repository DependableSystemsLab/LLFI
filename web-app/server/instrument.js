var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";


exports.processInstrument = function (req, res) {

	var fileName = req.body.fileName;
	console.log(fileName);

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var generateMakeCmd = LLFI_BUILD_ROOT + "tools/GenerateMakefile --readable --all -o " + fileName + ".ll";


	var commands = [cdDirCmd + " && " + generateMakeCmd, cdDirCmd + " && " + "make"];

	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		// all done here, all results in the results array
		console.log("Instrument success", results);
	}, function(err) {
		// error here
	});
}



var execPromise = function(cmd) {
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			if (err) return reject(err);
			resolve(stdout);
		});
	});
}
