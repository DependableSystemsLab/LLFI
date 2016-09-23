var React = require("react");
var ProfilingStatus = require("./outputTabs/profilingStatus");
var FaultInjectionStatus = require("./outputTabs/faultInjectionStatus");
var FaultSummary = require("./outputTabs/faultSummary");


var OutputSummary = React.createClass({
	getInitialState: function(){
		return {
 			selectedTab: 'profilingStatus'
		};
	},
	render: function() {
		return (
			<div class="outputSummaryWindow">
				<ul class="nav nav-tabs outputTabs">
					<li class={this.state.selectedTab === "profilingStatus" ? "active" : ''} onClick={()=> this.onTabChange("profilingStatus")}>
						<a>Profiling Status</a>
					</li>
					<li class={this.state.selectedTab === "faultInjectionStatus" ? "active" : ''} onClick={()=> this.onTabChange("faultInjectionStatus")}>
						<a>Fault Injection Status</a>
					</li>
					<li class={this.state.selectedTab === "faultSummary" ? "active" : ''} onClick={()=> this.onTabChange("faultSummary")}>
						<a>Fault Summary</a>
					</li>
					<li class={this.state.selectedTab === "errorDisplay" ? "active" : ''} onClick={()=> this.onTabChange("errorDisplay")}>
						<a>Error Display</a>
					</li>
					<li class={this.state.selectedTab === "console" ? "active" : ''} onClick={()=> this.onTabChange("console")}>
						<a>Console</a>
					</li>
				</ul>
				<ProfilingStatus shouldDisplay={this.state.selectedTab === "profilingStatus" ? true : false}></ProfilingStatus>
				<FaultInjectionStatus shouldDisplay={this.state.selectedTab === "faultInjectionStatus" ? true : false}></FaultInjectionStatus>
				<FaultSummary shouldDisplay={this.state.selectedTab === "faultSummary" ? true : false}></FaultSummary>
			</div>
		);
	},
	onTabChange: function(tabName) {
		this.setState({
			selectedTab: tabName
		});
	},
});

module.exports = OutputSummary;