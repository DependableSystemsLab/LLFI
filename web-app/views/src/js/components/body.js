var React = require("react");
var Tabs = require('./tabs');
var Tools = require('./tools');
var WindowLayout = require('./mainWindow/windowLayout');

var Body = React.createClass({
	render: function() {
		return (
			<div className = "body">
				<Tabs></Tabs>
				<Tools></Tools>
				<hr/>
				<WindowLayout/>
			</div>
		);
	}
});

module.exports = Body;