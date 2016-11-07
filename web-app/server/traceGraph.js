var fs = require('fs');
var readline = require('readline');
var exec = require('child_process').exec;
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processTrace = function (req, res) {

	var runNumbers = req.body.selectedRuns;

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
			}, function(err) {
				console.log("fault injection err: ", err);
			});
		});
	}, Promise.resolve([])).then(function(results) {
		var statOutputDir = "./uploads/" + req.ip +"/llfi/llfi_stat_output/";
		var totalRunCount = 0;
		// Get the total number of Runs
		fs.readdir(statOutputDir, (err, files) => {
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
			console.log("Trace success");
		})
	});
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