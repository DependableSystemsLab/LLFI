var Reflux = require("reflux");

var fileUploadActions = Reflux.createActions([
    'addFile',
    'addFiles',
    'fetchFile'
    ]);

module.exports = fileUploadActions;