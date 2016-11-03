var fs = require('fs');
var readline = require('readline');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

// Do a hardware and software auto scan, send the applicable injection types back to the client
exports.processPreInstrument = function (req, res) {
	var fileName = req.body.fileName;

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var softwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/SoftwareFailureAutoScan --no_input_yaml " + fileName + ".ll";
	var hardwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/HardwareFailureAutoScan --no_input_yaml " + fileName + ".ll";

	var commands = [];

	commands.push(cdDirCmd + " && " + softwareFailureAutoScanCmd);
	commands.push(cdDirCmd + " && " + hardwareFailureAutoScanCmd);

	var hardwareInjectionTypes = [];
	var softwareInjectionTypes = [];
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
		// Read hardware injection types
		var hardwareFile = "./uploads/" + req.ip +"/llfi.applicable.hardware.selectors.txt";
		var read = true;
		fs.readFileSync(hardwareFile).toString().split('\n').forEach(function (line) {
			if (line.includes("regSelMethod:")) read = false;
			if (read && line.includes("- ")) {
				var injectionType = line.substring(line.indexOf("- ")+ 2);
				hardwareInjectionTypes.push(injectionType);
			}
		});
	}).then(function(){
		var injectionTypes = {softwareInjectionTypes: softwareInjectionTypes, hardwareInjectionTypes: hardwareInjectionTypes};
		res.send(injectionTypes);
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
