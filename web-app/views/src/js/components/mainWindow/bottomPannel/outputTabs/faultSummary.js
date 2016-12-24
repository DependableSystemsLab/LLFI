var React = require("react");
var faultSummaryStore = require("./../../../../stores/faultSummaryStore");
var Reflux = require("reflux");


var FaultSummary = React.createClass({
	mixins: [Reflux.connect(faultSummaryStore,"faultSummary")],
	getInitialState: function() {
		return {
			faultSummary: {SDC: 0, Hanged: 0, Crashed: 0}
		};
	},
	componentDidUpdate: function () {
		this._drawChart();
	},
	render: function() {
		var className = "faultSummary" + (this.props.shouldDisplay ? "" : " hide");
		return (
			<div class={className}>
				<canvas id="faultSummary"></canvas>
			</div>
		);
	},
	_drawChart: function () {
		var horizontalBarChartData = {
			labels: ["SDC", "Hanged", "Crashed"],
			datasets: [{
				label: 'Dataset 1',
				backgroundColor: "rgba(220,220,220,0.5)",
				data: [this.state.faultSummary.SDC, this.state.faultSummary.Hanged, this.state.faultSummary.Crashed]
			}]
		};
		var ctx = document.getElementById("faultSummary").getContext("2d");
		window.myHorizontalBar = new Chart(ctx, {
			type: 'horizontalBar',
			data: horizontalBarChartData,
			options: {
				// Elements options apply to all of the options unless overridden in a dataset
				// In this case, we are setting the border of each horizontal bar to be 2px wide and green
				elements: {
					rectangle: {
						borderWidth: 1,
						borderColor: 'rgb(0, 255, 0)',
						borderSkipped: 'left'
					}
				},
				responsive: true,
				legend: {
					position: 'right',
				},
				title: {
					display: true,
					text: 'Fault Summary'
				}
			}
		});
	}
});

module.exports = FaultSummary;