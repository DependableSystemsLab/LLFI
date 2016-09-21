var React = require("react");
var Tabs = require('./tabs');
var Tools = require('./tools');

var Body = React.createClass({
	render: function() {
		return (
			<div className = "body">
				<Tabs></Tabs>
				<Tools></Tools>
				<hr/>
			</div>
		);
	}
});

module.exports = Body;