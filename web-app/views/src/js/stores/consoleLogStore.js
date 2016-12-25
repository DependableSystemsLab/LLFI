var Reflux = require("reflux");
var consoleLogActions = require("./../actions/consoleLogActions");
var consoleLog = "";
var consoleLogStore = Reflux.createStore({
	listenables: [consoleLogActions],

	onUpdateConsoleLog: function(consoleLogs) {
		consoleLog = "";
		for (var i = 0; i < consoleLogs.length; i++) {
			if (consoleLogs[i]) {
				consoleLog += consoleLogs[i] + "\n";
			}
		}
		this.trigger(consoleLog);
	},
});

module.exports = consoleLogStore;