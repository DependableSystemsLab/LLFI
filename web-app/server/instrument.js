var fs = require('fs');
var LLFI_BUILD_ROOT = "./../../../../installer/llfi/";

exports.processInstrument = function (req, res) {

	// Create a stream for input.yaml file
	var stream = fs.createWriteStream("./uploads/"+ req.ip +"/input.yaml");

	// Contents of the input.yaml file
	stream.once('open', function(fd) {
		stream.write("kernelOption: [forceRun]\n");
		stream.write("compileOption:\n");
		stream.write("  instSelMethod:\n");
		stream.write("  - customInstselector:\n");
		stream.write("      include: [CPUHog(Res), DataCorruption(Data), HighFrequentEvent(Timing)]\n");
		stream.write("  regSelMethod: customregselector\n");
		stream.write("  customRegSelector: Automatic\n");
		stream.write("  includeInjectionTrace: [forward, backward]\n");
		stream.write("  tracingPropagation: true\n");
		stream.write("  tracingPropagationOption: {debugTrace: True/False, generateCDFG: true}\n");
		stream.end();
	});
	res.end();
}