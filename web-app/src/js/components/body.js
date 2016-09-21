var React = require("react");
var Tabs = require('./tabs');
var Tools = require('./tools');
var MainWindows = require('./MainWindows');

var Body = React.createClass({
	render: function() {
		return (
			<div className = "body">
				<Tabs></Tabs>
				<Tools></Tools>
				<hr/>
				<MainWindows/>
			</div>
		);
	}
});

module.exports = Body;