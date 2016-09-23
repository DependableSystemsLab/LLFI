var React = require("react");
var ProfilingStatus = require("./outputTabs/profilingStatus");


var OutputSummary = React.createClass({
	render: function() {
		var displayedTab = (<ProfilingStatus></ProfilingStatus>);
		return (
			<div className="outputSummaryWindow">
				<ul className="nav nav-tabs outputTabs">
					<li className="active">
						<a>Profiling Status</a>
					</li>
					<li><a>Fault Injection Status</a></li>
					<li><a>Fault Summary</a></li>
					<li><a>Error Display</a></li>
					<li><a>Console</a></li>
				</ul>
				{displayedTab}
			</div>
		);
	}
});

module.exports = OutputSummary;