var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";
var execPromise = require('./utils/execPromise').execPromise;

exports.processProfiling = function (req, res) {

	var fileName = req.body.fileName;
	// Remove the file extension
	fileName = fileName.replace(/\.[^/.]+$/, "");
	var input = req.body.input;
	var injectionMode = req.body.injectionMode.injectionMode;
	var injectionType = req.body.injectionMode.injectionType;
	var profilingType = injectionMode == "hardware" ? "Hardware Fault(s)" : injectionType[0];
	var batchMode = req.body.injectionMode.isBatchMode;
	var profilingScript;
	if (batchMode) {
		profilingScript = LLFI_BUILD_ROOT + "bin/batchProfile " + fileName + ".ll " + input;
	} else {
		profilingScript = LLFI_BUILD_ROOT + "bin/profile " + "./llfi/" + fileName + "-profiling.exe " + input;
	}

	var cdDirCmd = "cd ./uploads/" + req.ip +"/";
	var consoleLog = [];
	var commands = [];
	commands.push(cdDirCmd + " && " + profilingScript);

	commands.reduce(function(p, cmd) {
		return p.then(function(results) {
			return execPromise(cmd).then(function(stdout) {
				results.push(stdout);
				consoleLog = results;
				return results;
			});
		});
	}, Promise.resolve([])).then(function(results) {
		var totalIndexFilePath = "./uploads/" + req.ip +"/" + "llfi.stat.totalindex.txt";
		fs.readFile(totalIndexFilePath, 'utf8', function(err, data) {
			var totalIndex = parseInt(data.split("=")[1]);
			var profilingStatsFilePath = "./uploads/" + req.ip +"/" + "llfi.stat.prof.txt";
			fs.readFile(profilingStatsFilePath, 'utf8', function(err, data) {
				var lastCycle = parseInt(data.split("=")[1])
				lastCycle = lastCycle == 0 ? 0 : lastCycle -1 ;
				var profilingStats = [{type: profilingType, lastIndex: totalIndex, lastCycle: lastCycle}];
				console.log("Profiling success");
				var result = {profilingStats: profilingStats, consoleLog: consoleLog}
				res.send(result);
			});
		});
	});
}