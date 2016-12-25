var React = require("react");
var consoleLogStore = require("./../../../../stores/consoleLogStore");
var Reflux = require("reflux");

var Console = React.createClass({
	mixins: [Reflux.connect(consoleLogStore,"consoleLog")],
	getInitialState: function() {
		return {
			consoleLog: ''
		};
	},
	render: function() {
		var className = "console" + (this.props.shouldDisplay ? "" : " hide");
		return (
			<div class={className}>
				<textarea value={this.state.consoleLog} class="consoleBox disabled" id="console" rows="10" readOnly>
				</textarea>
			</div>
		);
	}
});

module.exports = Console;