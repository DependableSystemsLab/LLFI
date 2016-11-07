var Reflux = require("reflux");
var faultInjectionStatusActions = require("./../actions/faultInjectionStatusActions");
var faultInjectionStatus = [];
var faultInjectionStatusStore = Reflux.createStore({
	listenables: [faultInjectionStatusActions],

	onUpdateFaultInjectionStatus: function(data) {
		faultInjectionStatus = data;
		this.trigger(faultInjectionStatus);
	},
});

module.exports = faultInjectionStatusStore;