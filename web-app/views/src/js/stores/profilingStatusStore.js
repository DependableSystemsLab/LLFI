var Reflux = require("reflux");
var profilingStatusActions = require("./../actions/profilingStatusActions");
var profilingStatus = [];
var profilingStatusStore = Reflux.createStore({
	listenables: [profilingStatusActions],

	onUpdateProfilingStatus: function(data) {
		profilingStatus = data;
		this.trigger(profilingStatus);
	},
});

module.exports = profilingStatusStore;