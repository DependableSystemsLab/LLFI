var fs = require('fs');
var readline = require('readline');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processTrace = function (req, res) {

	var traceRunNumbers = req.body.selectedRuns;
	var traceFolder = "./uploads/" + req.ip +"/llfi/trace_report_output/";
	// Make a dir to store the files from a client
	if (!fs.existsSync(traceFolder)) {
		fs.mkdirSync(traceFolder);
	}

	var goldenFile = "./uploads/" + req.ip +"/llfi/baseline/llfi.stat.trace.prof.txt";
	var llfi_stat_output = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
	var runNumbers = [];
	var selectedTraceFileNames = [];
	// Get the number of runs in each run option
	fs.readdir(llfi_stat_output, (err, files) => {
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
	})

	// commands.push(cdDirCmd + " && " + faultInjectionScript);

	// commands.reduce(function(p, cmd) {
	// 	return p.then(function(results) {
	// 		return execPromise(cmd).then(function(stdout) {
	// 			results.push(stdout);
	// 			consoleLog = results;
	// 			return results;
	// 		}, function(err) {
	// 			console.log("fault injection err: ", err);
	// 		});
	// 	});
	// }, Promise.resolve([])).then(function(results) {
	// 	var statOutputDir = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
	// 	var totalRunCount = 0;
	// 	// Get the total number of Runs
	// });
}

var execPromise = function(cmd) {
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			if (err) return reject(err);
			resolve(cmd + stdout);
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