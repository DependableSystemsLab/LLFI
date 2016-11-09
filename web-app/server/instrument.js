var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";
var execPromise = require('./utils/execPromise').execPromise;
var errorStatus = false;

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
	var batchMode = injectionMode == "software" && injectionType.length > 1 ? true : false;
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
		if(injectionMode == "software") {		
			stream.write("  - customInstselector:\n");
			var instrumentTypeStr = "      include: [";
			instrumentTypeStr += injectionType.join(", ");
			instrumentTypeStr += "]\n";
			stream.write(instrumentTypeStr);
			stream.write("  regSelMethod: customregselector\n");
			stream.write("  customRegSelector: Automatic\n");
		} else if (injectionMode == "hardware") {
			stream.write("  - insttype:\n");
			var instrumentTypeStr = "      include: [";
			instrumentTypeStr += injectionType.join(", ");
			instrumentTypeStr += "]\n";
			stream.write(instrumentTypeStr);
			stream.write("  regSelMethod: regloc\n");
			stream.write("  regloc: " + registerLocation + "\n");
		}
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

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";

	var softwareFailureAutoScanCmd = LLFI_BUILD_ROOT + "bin/SoftwareFailureAutoScan --no_input_yaml " + fileName + ".ll";

	var commands = [];

	commands.push(cdDirCmd + " && " + softwareFailureAutoScanCmd);
	commands.push(cdDirCmd + " && " + intrumentScript);
	var consoleLog = [];
	var files = [];
	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				consoleLog = results;
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		if (batchMode) {
			// Copy the llfi.stat.graph.doc file
			fs.createReadStream("./uploads/" + req.ip +"/llfi-" + injectionType[0]+"/llfi.stat.graph.dot").pipe(fs.createWriteStream("./uploads/" + req.ip +"/llfi.stat.graph.dot"));
			var indexFilePath = "./uploads/" + req.ip +"/llfi-" + injectionType[0]+"/llfi/" + fileName + "-llfi_index.ll";
		} else {
			var indexFilePath = "./uploads/" + req.ip +"/llfi/" + fileName + "-llfi_index.ll";
		}
		// Generate the llfi_displayIndex.ll file
		var outputIndexFilePath = "./uploads/" + req.ip +"/" + fileName + "-llfi_displayIndex.ll";
		var index = 1;
		fs.readFileSync(indexFilePath).toString().split('\n').forEach(function (line) {
			var modefiedLine = line;
			if (line.includes("!llfi_index !")) {
				modefiedLine = index + "\t\t" + line.substring(0, line.indexOf("!llfi_index !"))
				index ++;
				fs.appendFileSync(outputIndexFilePath, modefiedLine.toString() + "\n");
			} else if (!line.includes("= metadata !")) {
				modefiedLine = "\t\t" + line;
				fs.appendFileSync(outputIndexFilePath, modefiedLine.toString() + "\n");
			}
		});

		// Send the llfi_displayIndex file back to front-end
		fs.readFile(outputIndexFilePath, 'utf8', function(err, data) {
			if (err) {
				res.status(500);
				res.send(err);
				errorStatus = true;
				console.log("err in file reading, ", err);
			}
			if (errorStatus) return;
			var fileObj = {};
			fileObj.fileName = fileName + "-llfi_displayIndex.ll";
			fileObj.fileContent = data;
			files.push(fileObj);
			var result = {files: files, consoleLog: consoleLog}
			console.log("Instrument success");
			res.send(result);
		});
	}, function(err) {
		// error here
		if (errorStatus) return;
		res.status(500);
		res.send({error: err});
		console.log("err in Instrument process", err);
		errorStatus = true;
	});


}