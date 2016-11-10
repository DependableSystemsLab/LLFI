var Reflux = require("reflux");
var faultSummaryActions = require("./../actions/faultSummaryActions");
var faultSummary = {SDC: 0, Hanged: 0, Crashed: 0};
var faultSummaryStore = Reflux.createStore({
	listenables: [faultSummaryActions],

	onUpdateFaultSummary: function(data) {
		faultSummary = data;
		this.trigger(faultSummary);
	},
});

module.exports = faultSummaryStore;