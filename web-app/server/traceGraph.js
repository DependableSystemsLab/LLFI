var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = require('./utils/config').LLFI_BUILD_ROOT;
var execPromise = require('./utils/execPromise').execPromise;
var errorStatus = false;

exports.processTrace = function (req, res) {

	var traceRunNumbers = req.body.selectedRuns;
	var traceFolder = "./uploads/" + req.ip +"/llfi/trace_report_output/";
	// Make a dir to store the files from a client
	if (!fs.existsSync(traceFolder)) {
		fs.mkdirSync(traceFolder);
	}

	var goldenFile = "./llfi/baseline/llfi.stat.trace.prof.txt";
	var llfi_stat_output = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
	var runNumbers = [];
	var selectedTraceFileNames = [];
	var traceDiffFileNames = []
	var commands = [];
	var consoleLog = [];
	var cdDirCmd = "cd ./uploads/" + req.ip +"/";
	// Get the number of runs in each run option
	fs.readdir(llfi_stat_output, (err, files) => {
		if (err) {
			res.status(500);
			res.send(err);
			errorStatus = true;
			console.log("err in file reading, ", err);
		}
		if (errorStatus) return;
		files.forEach(file => {
			// Get the stats of each run
			if (file.includes("llfi.stat.fi.injectedfaults")) {
				var fileName = file;
				var runOptionNumber = fileName.split("llfi.stat.fi.injectedfaults.")[1];
				runOptionNumber = parseInt(runOptionNumber.split("-")[0]);
				if (!runNumbers[runOptionNumber]) {
					runNumbers[runOptionNumber] = 1;
				} else {
					runNumbers[runOptionNumber]++;
				}
			}
		});
		// Get the selected Trace file names
		var currentRunOptionNumber = 0;
		var currentRunNumberOffset = 0;
		for (var i = 0; i < traceRunNumbers.length; i++) {
			var traceNumber = traceRunNumbers[i] - currentRunNumberOffset;
			while (traceNumber >= runNumbers[currentRunOptionNumber]) {
				currentRunNumberOffset += runNumbers[currentRunOptionNumber];
				traceNumber -= runNumbers[currentRunOptionNumber];
				currentRunOptionNumber ++ ;
			}
			selectedTraceFileNames.push("llfi.stat.trace." + currentRunOptionNumber + "-" + traceNumber + ".txt");
		}

		// TraceDiff commands
		for (var i = 0; i < selectedTraceFileNames.length; i++) {
			if (files.indexOf(selectedTraceFileNames[i]) > -1) {
				var nameParser = selectedTraceFileNames[i].split("llfi.stat.trace.")[1];
				var runOption = parseInt(nameParser.split("-")[0]);;
				var runNumber = nameParser.split("-")[1];;
				runNumber = parseInt(runNumber.split(".txt")[0]);;
				var tradeDiffFileName = "TraceDiffReportFile." + runOption + "-" + runNumber + ".txt";
				traceDiffFileNames.push(tradeDiffFileName);
				var tradeFile = "./llfi/llfi_stat_output/" + selectedTraceFileNames[i];
				var command = LLFI_BUILD_ROOT + "tools/tracediff " + goldenFile + " " + tradeFile + " > " + "./llfi/trace_report_output/" + tradeDiffFileName;

				commands.push(cdDirCmd + " && " + command);
			}
		}

		//Trace Union command
		var traceUnionCmd = LLFI_BUILD_ROOT + "tools/traceunion ";
		for (var i = 0; i < traceDiffFileNames.length; i++) {
			traceUnionCmd += "./llfi/trace_report_output/" + traceDiffFileNames[i] + " ";
		}
		traceUnionCmd += "> ./llfi/trace_report_output/UnionedDiffReportFile.txt";
		commands.push(cdDirCmd + " && " + traceUnionCmd)

		// traceontograph command
		var tracetoGraphCmd = LLFI_BUILD_ROOT + "tools/traceontograph ./llfi/trace_report_output/UnionedDiffReportFile.txt ./llfi.stat.graph.dot > ./llfi/trace_report_output/TraceGraph.dot";
		commands.push(cdDirCmd + " && " + tracetoGraphCmd)

		//Covert dot file to pdf file
		var traceCovertCmd = "dot -Tpdf ./llfi/trace_report_output/TraceGraph.dot -o ./llfi/trace_report_output/TraceGraph.pdf";
		commands.push(cdDirCmd + " && " + traceCovertCmd)

		//Execute the commands
		commands.reduce(function(p, cmd) {
			return p.then(function(results) {
				return execPromise(cmd).then(function(stdout) {
					results.push(stdout);
					consoleLog = results;
					return results;
				}, function(err) {
					console.log("Trace onto graph err: ", err);
				});
			});
		}, Promise.resolve([])).then(function(results) {
			if (errorStatus) return;
			res.send({consoleLog: consoleLog});
		}, function(err) {
			// error here
			if (errorStatus) return;
			res.status(500);
			res.send({error: err});
			console.log("err in traceGraph process", err);
			errorStatus = true;
		});
	});
}

// Parse the file data to get the value of a status
var getStatusValue = function (statusType, fileData) {1
	var keyword = statusType + "=";
	var value = fileData.split(keyword)[1];
	value = value.split(",")[0];
	return value;
}