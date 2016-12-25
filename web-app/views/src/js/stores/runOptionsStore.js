var Reflux = require("reflux");
var runOptionsActions = require("./../actions/runOptionsActions");
var runOptions = [];
var runOptionsStore = Reflux.createStore({
	listenables: [runOptionsActions],

	onUpdateRunOptions: function(data) {
		runOptions = data;
		this.trigger(runOptions);
	},
});

module.exports = runOptionsStore;