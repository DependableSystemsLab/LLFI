var React = require("react");


var InputWindow = React.createClass({
	render: function() {
		return (
			<div className="inputWindow">
				<div className="inputWindowLabel">Command Line Input</div>
				<textarea className="inputTextArea" rows="5"></textarea>
			</div>
		);
	}
});

module.exports = InputWindow;