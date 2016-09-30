var React = require("react");

var Header = React.createClass({
	render: function() {
		return (
			<div className = "header">
				<div className= "row">
					<div className = "col-sm-2"></div>
					<div className = "col-sm-8">
						<div className="header-message">Welcome to LLFI Web Service </div>
					</div>
					<div className= "col-sm-2"></div>
				</div>
			</div>
		);
	}
});

module.exports = Header;