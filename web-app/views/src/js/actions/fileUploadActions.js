var Reflux = require("reflux");

var fileUploadActions = Reflux.createActions([
    'addFiles',
    'fetchFile'
    ]);

module.exports = fileUploadActions;