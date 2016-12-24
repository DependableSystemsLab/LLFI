var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = require('./utils/config').LLFI_BUILD_ROOT;
var execPromise = require('./utils/execPromise').execPromise;

exports.processFaultInjection = function (req, res) {

	var errorStatus = false;
	var fileName = req.body.fileName;
	var runOptions = req.body.runOptions;
	// Extract filename without extension
	fileName = fileName.replace(/\.[^/.]+$/, "");
	var input = req.body.input;
	var batchMode = req.body.injectionMode.isBatchMode;

	// Get the right injection command based on isBatchMode
	// Todo: Batch mode is not fully supproted, the results of fault injection does not support batch Mode yet
	var faultInjectionScript;
	if (batchMode) {
		faultInjectionScript = LLFI_BUILD_ROOT + "bin/batchInjectfault " + fileName + ".ll " + input;
	} else {
		faultInjectionScript = LLFI_BUILD_ROOT + "bin/injectfault " + "./llfi/" + fileName + "-faultinjection.exe " + input;
	}

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";
	var consoleLog = [];
	var commands = [];
	var faultInjectionStatus = [];
	var faultSummary = {SDC: 0, Hanged: 0, Crashed: 0};
	commands.push(cdDirCmd + " && " + faultInjectionScript);

	// Execute the fault injection
	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				consoleLog = results;
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		if (errorStatus) return;
		var statOutputDir = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
		var stdOutputDir = "./uploads/" + req.ip +"/llfi/std_output/";
		var errorDir = "./uploads/" + req.ip +"/llfi/error_output/";
		var currentRun = 0;
		var goldenOutputFile = "./uploads/" + req.ip +"/llfi/baseline/golden_std_output";
		var goldenOutput = "";
		// Read golden output
		fs.readFile(goldenOutputFile, 'utf8', function(err, data) {
			if (err) {
				res.status(500);
				res.send(err);
				errorStatus = true;
				console.log("err in file reading, ", err);
			}
			if (errorStatus) return;
			goldenOutput = data;

			// Get injection stats of each run
			for (var runOption = 0 ; runOption < runOptions.length; runOption++) {
				for (var run = 0; run < runOptions[runOption].numOfRuns; run++) {
						// Read stats from llfi.stat.fi.injectedfaults files
						var injectedfaultsStatsFileName = "llfi.stat.fi.injectedfaults." + runOption + "-" + run + ".txt";
						try {
							var injectedfaultsStatsData = fs.readFileSync(statOutputDir + injectedfaultsStatsFileName, 'utf8');
						} catch (err) {
							// If the file is not found, close the request, return error.
							// Todo: need to return the proper LLFI injection status when the [llfi.stat.fi.injectedfaults] file is not found
							res.status(500);
							res.send(err);
							errorStatus = true;
							console.log("err in file reading, ", err);
						}
						if (errorStatus) return;
						var runNumber = currentRun;
						var runIndex = runOption + "-" + run;
						var injectionType = getStatusValue("fi_type", injectedfaultsStatsData);
						var index = getStatusValue("fi_index", injectedfaultsStatsData);
						var cycle = getStatusValue("fi_cycle", injectedfaultsStatsData);
						var bit = getStatusValue("fi_bit", injectedfaultsStatsData);
						var status = "Injected";
						// Get SDC occurance stats
						var stdOutputFileName = "std_outputfile-run-" + runOption + "-" + run;
						try {
							var stdOutputData = fs.readFileSync(stdOutputDir + stdOutputFileName, 'utf8');
						} catch (err) {
							res.status(500);
							res.send(err);
							errorStatus = true;
							console.log("err in file reading, ", err);
						}
						if (errorStatus) return;
						var sdc = goldenOutput === stdOutputData ? "Not Occurred" : "Occurred";
						if (sdc === "Occurred") faultSummary.SDC ++;
						// Get result status
						var result = "Nil";
						var errorFileName = "errorfile-run-" + runOption + "-" + run;
						if (fs.existsSync(errorDir + errorFileName)) {
							try {
								var errorFileData = fs.readFileSync(errorDir + errorFileName, 'utf8');
							} catch (err) {
								res.status(500);
								res.send(err);
								errorStatus = true;
								console.log("err in file reading, ", err);
							}
							if (errorStatus) return;
							if (errorFileData.includes("hanged")) {
								result = "Hanged";
								faultSummary.Hanged ++;
							} else if (errorFileData.includes("crashed")) {
								result = "Crashed";
								faultSummary.Crashed ++;
							}
						}
						faultInjectionStatus[currentRun] = {runIndex, runNumber, injectionType, index, cycle, bit, sdc, result, status};
						currentRun ++;
				}
			}
			var results = {faultInjectionStatus, consoleLog, faultSummary};
			res.send(results);
			console.log("faultInjection success");
		});

	}, function(err) {
		// error here
		if (errorStatus) return;
		res.status(500);
		res.send({error: err});
		console.log("err in faultInjection process", err);
		errorStatus = true;
	});
};

// Parse the file data to get the value of a status
var getStatusValue = function (statusType, fileData) {
	var keyword = statusType + "=";
	var value = fileData.split(keyword)[1];
	value = value.split(",")[0];
	return value;
};