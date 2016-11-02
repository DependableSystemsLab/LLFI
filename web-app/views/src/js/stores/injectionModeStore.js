var Reflux = require("reflux");
var injectionModeActions = require("./../actions/injectionModeActions");

var injectionMode = {
	isBatchMode: false,
	injectionMode: ""
};
var injectionModeStore = Reflux.createStore({
	listenables: [injectionModeActions],
	onInjectionModeChange: function(injectMode) {
		injectionMode = injectMode;
		this.trigger(injectionMode);
	}
});

module.exports = injectionModeStore;