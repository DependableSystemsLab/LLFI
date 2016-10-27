var exec = require('child_process').exec;

exports.execPromise = function(cmd) {
	console.log("exec");
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			console.log("stdout" + stdout);
			if (err) return reject(err);
			resolve(stdout);
		});
	});
}
