var React = require("react");
var Reflux = require("reflux");
var Tutorial = require("./mainPannel/tutorial");
var fileUploadStore = require("./../../stores/fileUploadStore");
var fileUploadActions = require("./../../actions/fileUploadActions");

var MainPannel = React.createClass({
	mixins: [Reflux.connect(fileUploadStore,"fileList")],
	getInitialState: function() {
		return {
			fileList: [],
			fileDisplayIndex: 0
		};
	},
	render: function() {
		var fileContent = this.state.fileList[this.state.fileDisplayIndex] ? this.state.fileList[this.state.fileDisplayIndex].fileContent : "";
		var fileList = this.state.fileList.map(function(file, index) {
			if (index == 0) {
				return (
					<li className="active" key={index}><a onClick={this.onFileChange.bind(this, index)}>{file.fileName}</a></li>
				);
			} else {
				return (
					<li key={index}><a onClick={this.onFileChange.bind(this, index)}>{file.fileName}</a></li>
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
					{fileContent.split(/\r\n?|\n|\u21B5/g).map(function(item, index) {
						return (
							<span key={index}>
								{item}
								<br/>
							</span>
						);
					})}
				</div>
				<Tutorial></Tutorial>
			</div>
		);
	},
	onFileChange: function(index, event) {
		this.setState({
			fileDisplayIndex: index
		});
		$(event.currentTarget).parent().siblings().removeClass("active");
		$(event.currentTarget).parent().addClass("active");
	}
});

module.exports = MainPannel;