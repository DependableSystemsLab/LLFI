var React = require("react");
var Tutorial = require("./mainPannel/tutorial");


var MainPannel = React.createClass({
	render: function() {
		return (
			<div className="tabbable tabs-left mainPannelContainer">
				<ul className="nav nav-tabs left-pannel">
					<li className="fileListLabel">List Of Files</li>
					<li className="divider"></li>
					<li className="active"><a onClick={this.onFileChange}>file1.c</a></li>
					<li><a onClick={this.onFileChange}>file2.c</a></li>
					<li><a onClick={this.onFileChange}>file3.java</a></li>
					<li><a onClick={this.onFileChange}>file4.java</a></li>
				</ul>
				<div className="tab-content file-context">
					<p>#include stdio.h</p>
					<p>main(argc, argv)</p>
					<p>int argc;</p>
					<p>char *argv[];</p>
					<p>  int i,fact, n;</p>
					<p>  n = atoi(argv[1]);   </p>     
					<p>  fact = 1;</p>
					<p>    fact = fact * i;</p>
					<p>  printf("%d\n",fact);</p>
				</div>
				<Tutorial></Tutorial>
			</div>
		);
	},
	onFileChange: function(event) {
		$(event.currentTarget).parent().siblings().removeClass("active");
		$(event.currentTarget).parent().addClass("active");
	}
});

module.exports = MainPannel;