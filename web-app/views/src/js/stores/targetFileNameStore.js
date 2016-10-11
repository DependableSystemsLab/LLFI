var Reflux = require("reflux");
var targetFileNameActions = require("./../actions/targetFileNameActions");
var fileName ='';
var targetFileNameStore = Reflux.createStore({
	listenables: [targetFileNameActions],
	onChangeFileName: function(fileName) {
		fileName = fileName;
		this.trigger(fileName);
	}
});

module.exports = targetFileNameStore;