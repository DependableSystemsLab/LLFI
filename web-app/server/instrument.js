var fs = require('fs');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processInstrument = function (req, res) {

	var fileName = req.body.fileName;
	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var injectionMode = req.body.injectionMode;
	var injectionType = req.body.injectionType;
	var traceMode = req.body.traceMode;
	var backwardTrace = req.body.backwardTrace;
	var forwardTrace = req.body.forwardTrace;
	var maxTraceCount = req.body.maxTraceCount;
	var registerLocation = req.body.registerLocation;

	// Configurations for input.yaml file
	var batchMode = injectionMode == "hardware" || injectionType.length > 1 ? true : false;
	var intrumentScript = batchMode ? LLFI_BUILD_ROOT + "bin/batchInstrument --readable " + fileName + ".ll": LLFI_BUILD_ROOT + "bin/instrument -lpthread --readable " + fileName + ".ll";
	var traceEnabled = (traceMode == "fullTrace" && (backwardTrace || forwardTrace))|| tradeMode == "limitedTrace" ? true : false;
	if (traceEnabled) {
		var traceDirection = [];
		if (forwardTrace) traceDirection.push("forward");
		if (backwardTrace) traceDirection.push("backward");
	}
	// Create a stream for input.yaml file
	var stream = fs.createWriteStream("./uploads/"+ req.ip +"/input.yaml");

	// Contents of the input.yaml file
	stream.once('open', function(fd) {
		stream.write("kernelOption: [forceRun]\n");
		stream.write("compileOption:\n");
		stream.write("  instSelMethod:\n");
		stream.write("  - customInstselector:\n");
		var instrumentTypeStr = "      include: [";
		instrumentTypeStr += injectionType.join(", ");
		instrumentTypeStr += "]\n";
		stream.write(instrumentTypeStr);
		stream.write("  regSelMethod: customregselector\n");
		stream.write("  customRegSelector: Automatic\n");
		if (traceEnabled) {
			var traceDirectionStr = "  includeInjectionTrace: [";
			traceDirectionStr += traceDirection.join(", ");
			traceDirectionStr += "]\n";
			stream.write(traceDirectionStr);
			stream.write("  tracingPropagation: true\n");
			var traceOptionStr = "  tracingPropagationOption: {debugTrace: True/False, generateCDFG: true";
			if (traceMode == "limitedTrace") {
				traceOptionStr += ", maxTrace: " + maxTraceCount;
			}
			traceOptionStr += "}\n";
			stream.write(traceOptionStr);
		}
		stream.end();
	});

	var fileName = req.body.fileName;

	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var softwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/SoftwareFailureAutoScan --no_input_yaml " + fileName + ".ll";

	var commands = [cdDirCmd + " && " + softwareFailureAutoScanCmd, cdDirCmd + " && " + intrumentScript];

	commands.reduce(function(p, cmd) {
		console.log(cmd);
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				console.log(result);
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		console.log("Instrument success");

	});


	res.end();
}

var execPromise = function(cmd) {
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			console.log("err", err);
			if (err) return reject(err);
			resolve(stdout);
		});
	});
}
