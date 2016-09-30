var React = require("react");


var Footer = React.createClass({
	render: function() {
		return (
			<div className = "footer">
				<div className="footer-message">©Designed and Built by Kenneth Song</div>
				<div className="footer-message">Last Updated: 2016, September 14th</div>
			</div>
		);
	}
});

module.exports = Footer;