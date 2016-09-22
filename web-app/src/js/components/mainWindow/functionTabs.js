var React = require("react");
var FunctionTabs = React.createClass({
	render: function() {
		return (
			<div className = "functionTabs">
				<div className="btn-toolbar">
					<button className="btn btn-primary">Compile To IR</button>
					<button className="btn btn-primary">Instrument</button>
					<button className="btn btn-primary">Profiling</button>
					<button className="btn disabled">Runtime Options</button>
					<button className="btn disabled">Inject Fault</button>
					<button className="btn disabled">Trace Graph</button>
				</div>
			</div>
		);
	}
});

module.exports = FunctionTabs;