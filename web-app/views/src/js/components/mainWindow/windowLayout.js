var React = require("react");
var FunctionTabs = require("./functionTabs");
var MainPannel = require("./mainPannel");
var BottomPannel = require("./bottomPannel");

var WindowLayout = React.createClass({
	render: function() {
		return (
			<div className = "mainWindows">
				<div className="container-fluid">
					<FunctionTabs></FunctionTabs>
					<MainPannel></MainPannel>
					<BottomPannel></BottomPannel>
				</div>
			</div>
		);
	}
});

module.exports = WindowLayout;