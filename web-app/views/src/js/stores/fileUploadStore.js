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
			if (fileList.findIndex(file => file.fileName == files[i].fileName) >= 0) {
				// Replace the existing file if a file is already loaded
				var existingIndex = fileList.findIndex(file => file.fileName == files[i].fileName);
				fileList[existingIndex] = { fileName: files[i].fileName, fileContent: files[i].fileContent};
			} else {
				// Add the new file to the list
				fileList.push({
					fileName: files[i].fileName,
					fileContent: files[i].fileContent
				});
			}
		}
		this.trigger(fileList);
	}
});

module.exports = fileUploadStore;