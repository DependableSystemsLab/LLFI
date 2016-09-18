var React = require("react");


var Footer = React.createClass({
	render: function() {
		return (
			<div className = "footer">
				<div className = "footer-container">
					<div className="white">©Designed and Built by Kenneth Song</div>
					<div className="white footer-padding">Last Updated: 2016, September 14th</div>	
				</div>
			</div>
		);
	}
});

module.exports = Footer;