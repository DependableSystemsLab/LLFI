var React = require("react");


var OutputSummary = React.createClass({
	render: function() {
		return (
			<div className="outputSummaryWindow">
				<ul className="nav nav-tabs">
					<li className="active">
						<a>Profiling Status</a>
					</li>
					<li><a>Fault Injection Status</a></li>
					<li><a>Fault Summary</a></li>
					<li><a>Error Display</a></li>
					<li><a>Console</a></li>
				</ul>
			</div>
		);
	}
});

module.exports = OutputSummary;