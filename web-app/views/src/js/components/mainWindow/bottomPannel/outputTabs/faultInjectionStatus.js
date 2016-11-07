var React = require("react");
var faultInjectionStatusStore = require("./../../../../stores/faultInjectionStatusStore");
var Reflux = require("reflux");

var FaultInjectionStatus = React.createClass({
	mixins: [Reflux.connect(faultInjectionStatusStore,"faultInjectionStatus")],
	getInitialState: function() {
		return {
			faultInjectionStatus: []
		};
	},
	render: function() {
		var className = "faultInjectionStatus" + (this.props.shouldDisplay ? "" : " hide");
		var injectionStatusRows = this.state.faultInjectionStatus.map(function(data, index) {
			return (
				<tr key={index}>
					<td>{data.runOption}</td>
					<td>{data.injectionType}</td>
					<td>{data.index}</td>
					<td>{data.cycle}</td>
					<td>{data.bit}</td>
					<td>Not Occured</td>
					<td>Injected</td>
					<td>Nil</td>
					<td>
						<div class="checkbox">
							<input type="checkbox" value=""/>
						</div>
					</td>
				</tr>
			)
		});
		return (
			<div class={className}>
				<table class="table table-hover faultInjectionStatusTable">
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
							<th class="traceHeader">
								Trace
								<div class="checkbox">
									<label><input type="checkbox" value=""/>Select All</label>
								</div>
							</th>
						</tr>
					</thead>
					<tbody>
						{injectionStatusRows}
					</tbody>
				</table>
			</div>
		);
	}
});

module.exports = FaultInjectionStatus;