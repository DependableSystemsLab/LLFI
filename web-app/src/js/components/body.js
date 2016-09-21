var React = require("react");


var Body = React.createClass({
	render: function() {
		return (
			<div className = "body">
				<ul className="nav nav-tabs">
					<li className="active">
						<a href="#">Standard</a>
					</li>
					<li className="disabled">
						<a>Advanced</a>
					</li>
				</ul>
			</div>
		);
	}
});

module.exports = Body;