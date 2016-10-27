var Reflux = require("reflux");
var targetFileNameActions = require("./../actions/targetFileNameActions");
var fileName ='';
var targetFileNameStore = Reflux.createStore({
	listenables: [targetFileNameActions],
	onChangeFileName: function(Name) {
		fileName = Name;
		this.trigger(fileName);
	}
});

module.exports = targetFileNameStore;