var React = require("react");
var Reflux = require("reflux");
var Tutorial = require("./mainPannel/tutorial");
var fileUploadStore = require("./../../stores/fileUploadStore");
var fileUploadActions = require("./../../actions/fileUploadActions");

var MainPannel = React.createClass({
	mixins: [Reflux.connect(fileUploadStore,"fileList")],
	getInitialState: function() {
		return {
			fileList: []
		};
	},
	render: function() {
		var fileList = this.state.fileList.map(function(file, index) {
			console.log(index);
			if (index == 0) {
				return (
					<li className="active" key={index}><a onClick={this.onFileChange}>{file.fileName}</a></li>
				);
			} else {
				return (
					<li key={index}><a onClick={this.onFileChange}>{file.fileName}</a></li>
				);
			}
		}.bind(this));

		return (
			<div className="tabbable tabs-left mainPannelContainer">
				<ul className="nav nav-tabs left-pannel">
					<li className="fileListLabel">List Of Files</li>
					<li className="divider"></li>
					{fileList}
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