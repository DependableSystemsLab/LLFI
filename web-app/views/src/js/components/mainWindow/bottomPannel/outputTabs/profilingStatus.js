var React = require("react");
var profilingStatusStore = require("./../../../../stores/profilingStatusStore");
var Reflux = require("reflux");

var ProfilingStatus = React.createClass({
	mixins: [Reflux.connect(profilingStatusStore,"profilingStatus")],
	getInitialState: function() {
		return {
			profilingStatus: []
		};
	},
	render: function() {
		var className = "profilingStatus" + (this.props.shouldDisplay ? "" : " hide");
		var profilingRows = this.state.profilingStatus.map(function(data, index) {
			return (
				<tr key={index}>
					<td class="failureType">{data.type}</td>
					<td class="lastIndex">{data.lastIndex}</td>
					<td class="lastCycle">{data.lastCycle}</td>
				</tr>
			);
		});
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
						{profilingRows}
					</tbody>
				</table>
			</div>
		);
	}
});

module.exports = ProfilingStatus;