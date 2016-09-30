$('#fileUpload').on('change', function(){

	var files = $(this).get(0).files;

	if (files.length > 0){
		// One or more files selected, process the file upload

		// create a FormData object which will be sent as the data payload in the
		// AJAX request
		var formData = new FormData();

		// loop through all the selected files
		for (var i = 0; i < files.length; i++) {
			var file = files[i];

			// add the files to formData object for the data payload
			formData.append('uploads[]', file, file.name);
		}
		$.ajax({
			url: '/upload',
			type: 'POST',
			data: formData,
			processData: false,
			contentType: false,
			success: function(data){
				console.log('upload successful!');
			}
		});
	}
});
