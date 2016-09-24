var React = require("react");


var ErrorDisplay = React.createClass({
	render: function() {
		var className = "errorDisplay" + (this.props.shouldDisplay ? "" : " hide");

		return (
			<div class={className}>
				<textarea class="errorDisplayBox disabled" rows="10" readOnly></textarea>
			</div>
		);
	}
});

module.exports = ErrorDisplay;