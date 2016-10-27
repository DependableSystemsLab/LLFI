var fs = require('fs');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processInstrument = function (req, res) {

	// Create a stream for input.yaml file
	var stream = fs.createWriteStream("./uploads/"+ req.ip +"/input.yaml");

	// Contents of the input.yaml file
	stream.once('open', function(fd) {
		stream.write("kernelOption: [forceRun]\n");
		stream.write("compileOption:\n");
		stream.write("  instSelMethod:\n");
		stream.write("  - customInstselector:\n");
		stream.write("      include: [CPUHog(Res), DataCorruption(Data), HighFrequentEvent(Timing)]\n");
		stream.write("  regSelMethod: customregselector\n");
		stream.write("  customRegSelector: Automatic\n");
		stream.write("  includeInjectionTrace: [forward, backward]\n");
		stream.write("  tracingPropagation: true\n");
		stream.write("  tracingPropagationOption: {debugTrace: True/False, generateCDFG: true}\n");
		stream.end();
	});

	var fileName = req.body.fileName;

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var softwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/SoftwareFailureAutoScan --no_input_yaml " + fileName + ".ll";

	var commands = [cdDirCmd + " && " + softwareFailureAutoScanCmd];

	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		console.log("Instrument success");

	});


	res.end();
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
