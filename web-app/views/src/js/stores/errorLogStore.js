var Reflux = require("reflux");
var errorLogActions = require("./../actions/errorLogActions");
var errorLog = "";
var errorLogStore = Reflux.createStore({
	listenables: [errorLogActions],

	onUpdateErrorLog: function(errorLogs) {
		errorLog = errorLogs;
		this.trigger(errorLog);
	},
});

module.exports = errorLogStore;