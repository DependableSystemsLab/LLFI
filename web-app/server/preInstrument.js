var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = require('./utils/config').LLFI_BUILD_ROOT;
var execPromise = require('./utils/execPromise').execPromise;
var errorStatus = false;

// Do a hardware and software auto scan, send the applicable injection types back to the client
exports.processPreInstrument = function (req, res) {
	var fileName = req.body.fileName;

	// Extract filename without extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var softwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/SoftwareFailureAutoScan --no_input_yaml " + fileName + ".ll";
	var commands = [];

	commands.push(cdDirCmd + " && " + softwareFailureAutoScanCmd);

	var softwareInjectionTypes = [];

	// Execute the auto scan script
	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		// Read software injection types
		var softwareFile = "./uploads/" + req.ip +"/llfi.applicable.software.failures.txt";
		fs.readFileSync(softwareFile).toString().split('\n').forEach(function (line) {
			if (line.includes("- ")) {
				var injectionType = line.substring(line.indexOf("- ")+ 2);
				softwareInjectionTypes.push(injectionType);
			}
		});
	}, function(err) {
		// error here
		res.status(500);
		res.send({error: err});
		console.log("err in preInstrument process", err);
		errorStatus = true;
	}).then(function(){
		if (errorStatus) return;
		res.send(softwareInjectionTypes);
	});


}