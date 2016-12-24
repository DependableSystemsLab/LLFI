var React = require("react");
var Reflux = require("reflux");

var InstrumentModal = require('./instrumentModal');
var RuntimeOptionModal = require('./runtimeOptionModal');

var targetFileNameStore = require("./../../stores/targetFileNameStore");
var injectionModeStore = require("./../../stores/injectionModeStore");
var runOptionsStore = require("./../../stores/runOptionsStore");
var selectedTraceRunNumberStore = require("./../../stores/selectedTraceRunNumberStore");

var fileUploadActions = require("./../../actions/fileUploadActions");
var consoleLogActions = require("./../../actions/consoleLogActions");
var errorLogActions = require("./../../actions/errorLogActions");
var profilingStatusActions = require("./../../actions/profilingStatusActions");
var faultInjectionStatusActions = require("./../../actions/faultInjectionStatusActions");
var faultSummaryActions = require("./../../actions/faultSummaryActions");



var FunctionTabs = React.createClass({
	mixins: [Reflux.connect(targetFileNameStore,"fileName"),
		Reflux.connect(injectionModeStore,"injectionMode"),
		Reflux.connect(runOptionsStore,"runOptions"),
		Reflux.connect(selectedTraceRunNumberStore,"selectedTraceRunNumber")],
	getInitialState: function() {
		return {
			fileName: '',
			injectionMode: {},
			runOptions: [],
			selectedTraceRunNumber: []
		};
	},
	render: function() {
		return (
			<div class = "functionTabs">
				<div class="btn-toolbar">
					<button id="compileIRBtn" class={"btn " + (this.state.fileName ? "btn-primary" : "disabled")} onClick={this.onCompileIRClick}>Compile To IR</button>
					<button id="instrumentBtn" class="btn disabled" onClick={this.onInstrumentClick}>Instrument</button>
					<button id="profilingBtn" class="btn disabled" onClick={this.onProfilingClick}>Profiling</button>
					<button id="runtimeOptionBtn" class="btn disabled" onClick={this.onRuntimeOptionClick}>Runtime Options</button>
					<button id="injectFaultBtn" class="btn disabled" onClick={this.onFaultInjectionClick}>Inject Fault</button>
					<button id="traceGraphBtn" class="btn disabled" onClick={this.onGenerateTraceClick}>Trace Graph</button>
				</div>
				<InstrumentModal/>
				<RuntimeOptionModal/>
			</div>
		);
	},
	// CompileIR
	onCompileIRClick: function(event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		var data = {};
		data.fileName = this.state.fileName;
		$.ajax({
			url: '/compileIR',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				var consoleLog = data.consoleLog;
				var files = data.files;
				consoleLogActions.updateConsoleLog(consoleLog);
				fileUploadActions.addFiles(files);
				window.alert("Your program is successfully compiled to the IR format");
			},
			error: function (error) {
				if (error.responseJSON.error) {
					errorLogActions.updateErrorLog(error.responseJSON.error.cmd);
				}
				console.log(error);
				window.alert("An error has occured in compileIR, please refresh the page.");
			}
		});
		this.changeButtonStatus(event);
	},
	onInstrumentClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		$("#InstrumentModalID").click();
		this.changeButtonStatus(event);
	},
	onProfilingClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		var data = {};
		data.fileName = this.state.fileName;
		data.injectionMode = this.state.injectionMode;
		data.input = document.getElementById("profilingInput").value;
		$.ajax({
			url: '/profiling',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				var profilingStats = data.profilingStats;
				var consoleLog = data.consoleLog;
				profilingStatusActions.updateProfilingStatus(profilingStats);
				consoleLogActions.updateConsoleLog(consoleLog);
				console.log("profiling success");
				window.alert("Profiling Successful");
			},
			error: function (error) {
				if (error.responseJSON.error) {
					errorLogActions.updateErrorLog(error.responseJSON.error.cmd);
				}
				console.log(error);
				window.alert("An error has occured in Profiling, please refresh the page.");
			}
		});
		this.changeButtonStatus(event);
	},
	onRuntimeOptionClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		$("#RuntimeOptionModalID").click();
		this.changeButtonStatus(event);
	},
	onFaultInjectionClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		var data = {};
		data.fileName = this.state.fileName;
		data.injectionMode = this.state.injectionMode;
		data.input = document.getElementById("profilingInput").value;
		data.runOptions = this.state.runOptions;
		$.ajax({
			url: '/faultInjection',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				console.log(data);
				var consoleLog = data.consoleLog;
				var faultSummary = data.faultSummary;
				var faultInjectionStatus = data.faultInjectionStatus;
				faultInjectionStatusActions.updateFaultInjectionStatus(faultInjectionStatus);
				faultSummaryActions.updateFaultSummary(faultSummary);
				consoleLogActions.updateConsoleLog(consoleLog);
				console.log("faultInjection success");
				window.alert("FaultInjection Successful");
			},
			error: function (error) {
				if (error.responseJSON.error) {
					errorLogActions.updateErrorLog(error.responseJSON.error.cmd);
				}
				console.log(error);
				window.alert("An error has occured in FaultInjection, please refresh the page.");
			}
		});
		this.changeButtonStatus(event);
	},
	onGenerateTraceClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		var data = {};
		data.selectedRunIndex = this.state.selectedTraceRunNumber;
		$.ajax({
			url: '/traceGraph',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				var consoleLog = data.consoleLog;
				consoleLogActions.updateConsoleLog(consoleLog);
				// Simulate a download a tag to download the pdf trace file
				var a = document.createElement("a");
				a.href = "/tracepdf";
				a.download = "TraceGraph";
				document.body.appendChild(a);
				a.click();
				// remove the a tag after the download           
				document.body.removeChild(a);
				console.log("Generate Trace success");
			},
			error: function (error) {
				if (error.responseJSON.error) {
					errorLogActions.updateErrorLog(error.responseJSON.error.cmd);
				}
				console.log(error);
				window.alert("An error has occured in TraceGraph, please refresh the page.");
			}
		});
		this.changeButtonStatus(event);
	},
	changeButtonStatus: function(event) {
		// If the current button clicked is disabled, do nothing
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}

		// Disable all the following buttons and enable the next button only
		$("#"+event.currentTarget.id).nextAll().removeClass("btn-primary");
		$("#"+event.currentTarget.id).nextAll().addClass("disabled");
		$("#"+event.currentTarget.id).next().removeClass("disabled");
		$("#"+event.currentTarget.id).next().addClass("btn-primary");
	}
});

function compareNumbers(a, b) {
	return a - b;
}

module.exports = FunctionTabs;