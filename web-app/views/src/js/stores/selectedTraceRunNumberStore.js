var Reflux = require("reflux");
var selectedTraceRunNumberActions = require("./../actions/selectedTraceRunNumberActions");
var selectedRunNumber = [];
var selectedTraceRunNumberStore = Reflux.createStore({
	listenables: [selectedTraceRunNumberActions],

	onUpdateSelectedRunNumber: function(data) {
		selectedRunNumber = data;
		this.trigger(selectedRunNumber);
	},
});

module.exports = selectedTraceRunNumberStore;