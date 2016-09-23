var React = require("react");


var Console = React.createClass({
	render: function() {
		var className = "console" + (this.props.shouldDisplay ? "" : " hide");

		return (
			<div class={className}>
				<textarea class="consoleBox disabled" rows="10" readOnly></textarea>
			</div>
		);
	}
});

module.exports = Console;