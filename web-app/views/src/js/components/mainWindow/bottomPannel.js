var React = require("react");
var InputWindow = require("./bottomPannel/inputWindow");
var OutputSummary = require("./bottomPannel/outputSummary");



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