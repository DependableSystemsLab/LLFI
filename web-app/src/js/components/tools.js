var React = require("react");


var Tools = React.createClass({
	render: function() {
		return (
			<div class = "tools">
				<ul class="nav nav-pills">
					<li class="dropdown">
						<a class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Files</a>
						<ul class="dropdown-menu" role="menu" aria-labelledby="dropdownMenu">
							<li><a tabindex="-1">Open File</a></li>
							<li><a tabindex="-1">Import Project</a></li>
						</ul>
					</li>
					<li class="disabled"><a>Edit</a></li>
					<li class="disabled"><a>Help</a></li>
				</ul>
			</div>
		);
	}
});

module.exports = Tools;