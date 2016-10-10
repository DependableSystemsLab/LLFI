var Reflux = require("reflux");
var fileUploadActions = require("./../actions/fileUploadActions");
var fileList = [];
var fileName ='';
var fileUploadStore = Reflux.createStore({
	// this will set up listeners to all publishers in TodoActions, using onKeyname (or keyname) as callbacks
	listenables: [fileUploadActions],
	onAddFiles: function(file) {
		fileList.push({
			fileName: file.fileName,
			fileContent: file.fileContent
		});
		this.trigger(fileList);
	}
	// onUpdateProducts: function(files) {
	// 	this.files = files;
	// 	this.updateList(this.files);
	// },
	// // called whenever we change a list. normally this would mean a database API call
	// updateList: function(files){
	// 	this.trigger(this.files); // sends the updated list to all listening components (TodoApp)
	// }
});

module.exports = fileUploadStore;