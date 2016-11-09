var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";
var execPromise = require('./utils/execPromise').execPromise;
var errorStatus = false;

exports.processFaultInjection = function (req, res) {

	var fileName = req.body.fileName;
	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");
	var input = req.body.input;
	var batchMode = req.body.injectionMode.isBatchMode;
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
	commands.push(cdDirCmd + " && " + faultInjectionScript);

	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				consoleLog = results;
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		var statOutputDir = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
		var totalRunCount = 0;
		// Get the total number of Runs
		fs.readdir(statOutputDir, (err, files) => {
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
					var data = fs.readFileSync(statOutputDir + file, 'utf8');
					var runOption = totalRunCount;
					var injectionType = getStatusValue("fi_type", data);
					var index = getStatusValue("fi_index", data);
					var cycle = getStatusValue("fi_cycle", data);
					var bit = getStatusValue("fi_bit", data);
					faultInjectionStatus[totalRunCount] = {runOption, injectionType, index, cycle, bit};
					totalRunCount ++;
				}
			});
			var results = {faultInjectionStatus, consoleLog};
			res.send(results);
			console.log("faultInjection success");
		})
	}, function(err) {
		// error here
		if (errorStatus) return;
		res.status(500);
		res.send({error: err});
		console.log("err in faultInjection process", err);
		errorStatus = true;
	});
}

// Parse the file data to get the value of a status
var getStatusValue = function (statusType, fileData) {1
	var keyword = statusType + "=";
	var value = fileData.split(keyword)[1];
	value = value.split(",")[0];
	return value;
}