var React = require("react");
var InputWindow = require("./inputWindow");
var OutputSummary = require("./outputSummary");



var BottomPannel = React.createClass({
	render: function() {
		return (
			<div className="bottomPannel">
				<InputWindow></InputWindow>
				<OutputSummary></OutputSummary>
			</div>
		);
	}
});

module.exports = BottomPannel;