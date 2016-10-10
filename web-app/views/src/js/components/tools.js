var React = require("react");
var fileUploadActions = require("./../actions/fileUploadActions");
var targetFileNameActions = require("./../actions/targetFileNameActions");


var Tools = React.createClass({
	render: function() {
		return (
			<div class = "tools">
				<ul class="nav nav-pills">
					<li class="dropdown">
						<a class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Files</a>
						<ul class="dropdown-menu" role="menu" aria-labelledby="dropdownMenu">
							<li>
								<input ref="fileUpload" id="fileUpload" type="file" onChange={this.onFileUploaded}/>
								<a onClick={this.onClickFileUpload}>Upload File</a>
							</li>
							<li><a>Upload Project</a></li>
						</ul>
					</li>
					<li class="disabled"><a>Edit</a></li>
					<li class="disabled"><a>Help</a></li>
				</ul>
			</div>
		);
	},
	onClickFileUpload: function() {
		$("#fileUpload").click();
	},
	onFileUploaded: function() {
		var files = $("#fileUpload").get(0).files;
		if (files.length > 0) {
			// One or more files selected, process the file upload

			// create a FormData object which will be sent as the data payload in the
			// AJAX request
			var formData = new FormData();

			// loop through all the selected files
			for (var i = 0; i < files.length; i++) {
				var file = files[i];

				// add the files to formData object for the data payload
				formData.append('uploads[]', file, file.name);
				targetFileNameActions.changeFileName(file.name);
			}
			$.ajax({
				url: '/uploadFile',
				type: 'POST',
				data: formData,
				processData: false,
				contentType: false,
				success: function(data){
					fileUploadActions.addFiles(data);
				}
			});
		}
	}
});

module.exports = Tools;