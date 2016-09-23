var React = require("react");


var ProfilingStatus = React.createClass({
	render: function() {
		return (
			<div className="profilingStatus">
				<table className="table table-hover profilingStatusTable">
					<thead>
						<tr>
							<th className="failureType">Failure Type</th>
							<th className="lastIndex">Last Index</th>
							<th className="lastCycle">Last Cycle</th>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td className="failureType">1</td>
							<td className="lastIndex">2</td>
							<td className="lastCycle">3</td>
						</tr>
						<tr>
							<td className="failureType">1</td>
							<td className="lastIndex">2</td>
							<td className="lastCycle">3</td>
						</tr>
						<tr>
							<td className="failureType">1</td>
							<td className="lastIndex">2</td>
							<td className="lastCycle">3</td>
						</tr>
						<tr>
							<td className="failureType">1</td>
							<td className="lastIndex">2</td>
							<td className="lastCycle">3</td>
						</tr>
					</tbody>
				</table>
			</div>
		);
	}
});

module.exports = ProfilingStatus;