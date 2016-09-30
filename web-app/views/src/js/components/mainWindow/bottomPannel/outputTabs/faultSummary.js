var React = require("react");


var FaultSummary = React.createClass({
	render: function() {
		var className = "faultSummary" + (this.props.shouldDisplay ? "" : " hide");

		return (
			<div class={className}>
				<canvas id="faultSummary"></canvas>
			</div>
		);
	}
});

module.exports = FaultSummary;