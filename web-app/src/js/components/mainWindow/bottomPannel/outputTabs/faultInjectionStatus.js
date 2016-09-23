var React = require("react");


var FaultInjectionStatus = React.createClass({
	render: function() {
		return (
			<div className="faultInjectionStatus">
				<table className="table table-hover faultInjectionStatusTable">
					<thead>
						<tr>
							<th>Run Option</th>
							<th>Fault Injection Type</th>
							<th>Index</th>
							<th>Cycle</th>
							<th>Bit</th>
							<th>SDC Occurance</th>
							<th>Status</th>
							<th>Result</th>
							<th>Trace</th>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td>1</td>
							<td>bitflip</td>
							<td>33</td>
							<td>2</td>
							<td>29</td>
							<td>Not Occured</td>
							<td>Injected</td>
							<td>Nil</td>
							<td>
								<div class="checkbox">
									<input type="checkbox" value=""/>
								</div>
							</td>
						</tr>
					</tbody>
				</table>
			</div>
		);
	}
});

module.exports = FaultInjectionStatus;