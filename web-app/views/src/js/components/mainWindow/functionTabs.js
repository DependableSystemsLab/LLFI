var React = require("react");
var Reflux = require("reflux");
var InstrumentModal = require('./instrumentModal');
var RuntimeOptionModal = require('./runtimeOptionModal');
var targetFileNameStore = require("./../../stores/targetFileNameStore");
var injectionModeStore = require("./../../stores/injectionModeStore");
var fileUploadActions = require("./../../actions/fileUploadActions");
var consoleLogActions = require("./../../actions/consoleLogActions");
var profilingStatusActions = require("./../../actions/profilingStatusActions");
var faultInjectionStatusActions = require("./../../actions/faultInjectionStatusActions");
var selectedTraceRunNumberStore = require("./../../stores/selectedTraceRunNumberStore");



var FunctionTabs = React.createClass({
	mixins: [Reflux.connect(targetFileNameStore,"fileName"),
		Reflux.connect(injectionModeStore,"injectionMode"),
		Reflux.connect(selectedTraceRunNumberStore,"selectedTraceRunNumber")],
	getInitialState: function() {
		return {
			fileName: '',
			injectionMode: {},
			selectedTraceRunNumber: []
		};
	},
	render: function() {
		console.log(this.state);
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
		var data = {}
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
		var data = {}
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
		var data = {}
		data.fileName = this.state.fileName;
		data.injectionMode = this.state.injectionMode;
		data.input = document.getElementById("profilingInput").value;
		$.ajax({
			url: '/faultInjection',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				var consoleLog = data.consoleLog;
				var faultInjectionStatus = data.faultInjectionStatus;
				faultInjectionStatusActions.updateFaultInjectionStatus(faultInjectionStatus);
				consoleLogActions.updateConsoleLog(consoleLog);
				console.log("faultInjection success");
			}
		});
		this.changeButtonStatus(event);
	},
	onGenerateTraceClick: function (event) {
		if ($("#"+event.currentTarget.id).hasClass("disabled")) {
			return;
		}
		var data = {}
		data.selectedRuns = this.state.selectedTraceRunNumber;
		data.selectedRuns.sort(compareNumbers);
		$.ajax({
			url: '/traceGraph',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				console.log("Generate Trace success");
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