var React = require("react");


var ProfilingStatus = React.createClass({
	render: function() {
		var className = "profilingStatus" + (this.props.shouldDisplay ? "" : " hide");
		return (
			<div class={className}>
				<table class="table table-hover profilingStatusTable">
					<thead>
						<tr>
							<th class="failureType">Failure Type</th>
							<th class="lastIndex">Last Index</th>
							<th class="lastCycle">Last Cycle</th>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td class="failureType">Hardware Fault(s)</td>
							<td class="lastIndex">33</td>
							<td class="lastCycle">2</td>
						</tr>
						<tr>
							<td class="failureType">Hardware Fault(s)</td>
							<td class="lastIndex">33</td>
							<td class="lastCycle">2</td>
						</tr>
						<tr>
							<td class="failureType">Hardware Fault(s)</td>
							<td class="lastIndex">33</td>
							<td class="lastCycle">2</td>
						</tr>
						<tr>
							<td class="failureType">Hardware Fault(s)</td>
							<td class="lastIndex">33</td>
							<td class="lastCycle">2</td>
						</tr>
					</tbody>
				</table>
			</div>
		);
	}
});

module.exports = ProfilingStatus;