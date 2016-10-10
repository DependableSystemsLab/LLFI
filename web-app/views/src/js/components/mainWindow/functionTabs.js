var React = require("react");
var Reflux = require("reflux");
var fileUploadStore = require("./../../stores/targetFileNameStore");

var FunctionTabs = React.createClass({
	mixins: [Reflux.connect(fileUploadStore,"fileName")],
	getInitialState: function() {
		return {
			fileName: ''
		};
	},
	render: function() {
		console.log(this.state);
		return (
			<div class = "functionTabs">
				<div class="btn-toolbar">
					<button id="compileIRBtn" class="btn btn-primary" onClick={this.onInstrumentClick}>Compile To IR</button>
					<button id="instrumentBtn" class="btn disabled" onClick={this.onButtonClick}>Instrument</button>
					<button id="profilingBtn" class="btn disabled" onClick={this.onButtonClick}>Profiling</button>
					<button id="runtimeOptionBtn" class="btn disabled" onClick={this.onButtonClick}>Runtime Options</button>
					<button id="injectFaultBtn" class="btn disabled" onClick={this.onButtonClick}>Inject Fault</button>
					<button id="traceGraphBtn" class="btn disabled" onClick={this.onButtonClick}>Trace Graph</button>
				</div>
			</div>
		);
	},
	onInstrumentClick: function(event) {
		var data = {}
		data.fileName = this.state.fileName;
		console.log(this.state);
		$.ajax({
			url: '/instrument',
			type: 'POST',
			data: JSON.stringify(data),
			processData: false,
			contentType: 'application/json',
			success: function(data){
				console.log("instrument success.", data);
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

module.exports = FunctionTabs;