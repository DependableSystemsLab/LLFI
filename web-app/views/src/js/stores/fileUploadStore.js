var Reflux = require("reflux");
var fileUploadActions = require("./../actions/fileUploadActions");
var fileList = [];
var fileName ='';
var fileUploadStore = Reflux.createStore({
	listenables: [fileUploadActions],
	// Adding a single file to store
	onAddFile: function(file) {
		fileList.push({
			fileName: file.fileName,
			fileContent: file.fileContent
		});
		this.trigger(fileList);
	},
	// Adding an array of files to store
	onAddFiles: function(files) {
		for (var i = 0; i < files.length; i++) {
			fileList.push({
				fileName: files[i].fileName,
				fileContent: files[i].fileContent
			});
		}
		this.trigger(fileList);
	}
});

module.exports = fileUploadStore;