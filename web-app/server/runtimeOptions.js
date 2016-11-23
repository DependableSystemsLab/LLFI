var fs = require('fs');
var readline = require('readline');
var LLFI_BUILD_ROOT = require('./utils/config').LLFI_BUILD_ROOT;

exports.processRuntimeOptions = function (req, res) {

	var runtimeOptions = req.body.runtimeOptions;
	var inputYamlFilePath = "./uploads/"+ req.ip +"/input.yaml";
	var data = "";
	if (runtimeOptions.length) data += "runOption:\n";
	for (var j = 0; j < runtimeOptions.length; j ++) {
		var runOption = runtimeOptions[j];
		data += "- run: {";

		for(var keys = Object.keys(runOption), i = 0, end = keys.length - 1; i < end; i++) {
			var key = keys[i], value = runOption[key];
			data += key + ": " + value + ", ";
		}
		var lastIndex = Object.keys(runOption).length - 1;
		if(lastIndex >= 0) {
			var lastKey = Object.keys(runOption)[lastIndex];
			var value = runOption[lastKey];
			data += lastKey + ": " + value + "}\n";
		}
	}

	// Append the status to input yaml file
	fs.appendFile(inputYamlFilePath, data, function (err) {
		if (err) {
			res.status(500);
			res.send(err);
			console.log("err in modifying input.yaml file in runtimeOption: ", err);
		} else {
			console.log("runtimeOption Submit success");
			res.end();
		}

	});
}
