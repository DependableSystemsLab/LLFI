var React = require("react");
var errorLogStore = require("./../../../../stores/errorLogStore");
var Reflux = require("reflux");

var ErrorDisplay = React.createClass({
	mixins: [Reflux.connect(errorLogStore,"errorLog")],
	getInitialState: function() {
		return {
			errorLog: ''
		};
	},
	render: function() {
		var className = "errorDisplay" + (this.props.shouldDisplay ? "" : " hide");

		return (
			<div class={className}>
				<textarea value={this.state.errorLog} class="errorDisplayBox disabled" rows="10" readOnly></textarea>
			</div>
		);
	}
});

module.exports = ErrorDisplay;