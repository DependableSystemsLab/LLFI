var Reflux = require("reflux");
var targetFileNameActions = require("./../actions/targetFileNameActions");
var fileName ='';
var targetFileNameStore = Reflux.createStore({
	// this will set up listeners to all publishers in TodoActions, using onKeyname (or keyname) as callbacks
	listenables: [targetFileNameActions],
	onChangeFileName: function(fileName) {
		fileName = fileName;
		this.trigger(fileName);
	}
});

module.exports = targetFileNameStore;