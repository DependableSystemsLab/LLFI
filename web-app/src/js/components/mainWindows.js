var React = require("react");
var Tabs = require('./tabs');
var Tools = require('./tools');

var MainWindows = React.createClass({
	render: function() {
		return (
			<div className = "mainWindows">
				<div className="container-fluid">
					<div className="row-fluid">
						<div className="span3">
						3
						</div>
						<div className="span9">
						9
						</div>
					</div>
				</div>
			</div>
		);
	}
});

module.exports = MainWindows;