var React = require("react");


var Tools = React.createClass({
	render: function() {
		return (
			<div className = "tabs">
				<ul className="nav nav-pills">
					<li><a>Files</a></li>
					<li><a>Edit</a></li>
					<li className="disabled"><a>Help</a></li>
				</ul>
			</div>
		);
	}
});

module.exports = Tools;