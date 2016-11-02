var React = require('react');
var ReactDOM = require('react-dom');
var Reflux = require("reflux");
var Modal = require('react-bootstrap').Modal;
var FormGroup = require('react-bootstrap').FormGroup;
var FormControl = require('react-bootstrap').FormControl;
var Checkbox = require('react-bootstrap').Checkbox;
var Button = require('react-bootstrap').Button;
var ControlLabel = require('react-bootstrap').ControlLabel;
var FilteredMultiSelect = require('react-filtered-multiselect');

var RuntimeOptionModal = React.createClass({
	getInitialState() {
		return {
			show: false,
			runtimeOptions: []
		};
	},

	componentDidMount () {
		// Initial status of the UI elements
	},
	close() {
		this.setState({ show: false });
	},

	open() {
		this.setState({ show: true });
	},

	render: function() {
		return (
			<div class="modal-container" id="RuntimeOptionModalID" onClick={this.open}>
				<Modal {...this.props} bsSize="large" aria-labelledby="contained-modal-title-lg" onClick={this.open} show={this.state.show} onHide={this.close}>
					<Modal.Header closeButton>
						<Modal.Title id="contained-modal-title-lg">Run time Option</Modal.Title>
					</Modal.Header>
					<Modal.Body>
						<div class="rowContainer">
							<p class="boldFont leftFloat">Fault Injection Configuration</p>
							<button class="rightFloat">Delete Run</button>
						</div>
						<div class="rowContainer">
							<p class="boldFont leftFloat">Runtime Option:</p>
							<label>run <span id="runNumber">0</span></label>
						</div>
						<div>
							<label>Number Of Runs<span class="redColor">*</span></label>
							<input type="number" onChange={this.maxTraceCountHandler} min={1}></input>
						</div>

						<div class="rowContainer">
							<label>Random Seed</label>
							<input type="number"></input>
						</div>
						<div class="rowContainer">
							<label>TimeOut(ms)</label>
							<input type="number"></input>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<Button onClick={this.onClickInstrument}>Submit</Button>
					</Modal.Footer>
				</Modal>
			</div>
		);
	},

});

module.exports = RuntimeOptionModal;