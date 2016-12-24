var exec = require('child_process').exec;

exports.execPromise = function(cmd) {
	return new Promise(function(resolve, reject) {
		exec(cmd, function(err, stdout) {
			if (err) return reject(err);
			resolve(cmd + stdout);
		});
	});
};