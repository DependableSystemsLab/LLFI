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
var injectionModeStore = require("./../../stores/injectionModeStore");

var RuntimeOptionModal = React.createClass({
	mixins: [Reflux.connect(injectionModeStore,"injectionMode")],
	getInitialState() {
		return {
			show: false,
			runtimeOptions: [{}],
			injectionMode: {},
			runtimeOptionNumber: 0
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
		var softwareOptions = (
			<div class="modal-container" id="RuntimeOptionModalID" onClick={this.open}>
				<Modal {...this.props} bsSize="large" aria-labelledby="contained-modal-title-lg" onClick={this.open} show={this.state.show} onHide={this.close}>
					<Modal.Header closeButton>
						<Modal.Title id="contained-modal-title-lg">Run time Option</Modal.Title>
					</Modal.Header>
					<Modal.Body>
						<div class="runtimeContainer">
							<p class="boldFont leftFloat font-size-large">Fault Injection Configuration</p>
							<button class="rightFloat runtimeMargin">Delete Run</button>
						</div>
						<div class="runtimeContainer runtimeOptionContainer">
							<p class="boldFont leftFloat font-size-large">Runtime Option:</p>
							<label class="runtimeMargin alignCenter">run <span id="runNumber">{this.state.runtimeOptionNumber}</span></label>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Number Of Runs<span class="redColor">*</span></label>
							<input class="runtimeInputs" type="number" onChange={this.onChangeNumberofRuns} min={1}></input>
						</div>
						<div>
							<button>{"<"}</button>
							<button class="rightFloat">{">"}</button>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Random Seed</label>
							<input class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeRandomSeed}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>TimeOut(ms)</label>
							<input class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeTimeout}></input>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<Button onClick={this.onClickInstrument}>Submit</Button>
					</Modal.Footer>
				</Modal>
			</div>
		);
		var hardwareOptions = (
			<div class="modal-container" id="RuntimeOptionModalID" onClick={this.open}>
				<Modal {...this.props} bsSize="large" aria-labelledby="contained-modal-title-lg" onClick={this.open} show={this.state.show} onHide={this.close}>
					<Modal.Header closeButton>
						<Modal.Title id="contained-modal-title-lg">Run time Option</Modal.Title>
					</Modal.Header>
					<Modal.Body>
						<div class="runtimeContainer">
							<p class="boldFont leftFloat font-size-large">Fault Injection Configuration</p>
							<button class="rightFloat runtimeMargin">Delete Run</button>
						</div>
						<div class="runtimeContainer runtimeOptionContainer">
							<p class="boldFont leftFloat font-size-large">Runtime Option:</p>
							<label class="runtimeMargin alignCenter">run <span id="runNumber">{this.state.runtimeOptionNumber}</span></label>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Number Of Runs<span class="redColor">*</span></label>
							<input class="runtimeInputs" type="number" min={1} onChange={this.onChangeNumberofRuns}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Type<span class="redColor">*</span></label>
							<div class="runtimeInputs">
								<FormGroup controlId="faultInjectionType">
									<FormControl ref={"faultInjectionType"} componentClass="select" placeholder="select">
									<option value="bitflip">bitflip</option>
									<option value="stuck_at_0">stuck_at_0</option>
									<option value="stuck_at_1">stuck_at_1</option>
									</FormControl>
								</FormGroup>
							</div>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Cycles</label>
							<input class="runtimeInputs" type="number" placeholder="max:-1"></input>
						</div>
						<div>
							<button>{"<"}</button>
							<button class="rightFloat">{">"}</button>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Index</label>
							<input class="runtimeInputs" type="number" placeholder="max:34"></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Register Index</label>
							<input class="runtimeInputs" type="text" placeholder="null"></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Bit</label>
							<input class="runtimeInputs" type="text" placeholder="null"></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Random Seed</label>
							<input class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeRandomSeed}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>TimeOut(ms)</label>
							<input class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeTimeout}></input>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<Button onClick={this.onClickInstrument}>Submit</Button>
					</Modal.Footer>
				</Modal>
			</div>
		);
		return this.state.injectionMode.injectionMode && this.state.injectionMode.injectionMode == "software" ? softwareOptions : hardwareOptions;
	},
	onChangeNumberofRuns: function (event) {
		var runtimeOptions = this.state.runtimeOptions;
		runtimeOptions[this.state.runtimeOptionNumber].numberOfRuns = event.targe.value;
		this.setState({ runtimeOptions: runtimeOptions});
	},
	onChangeRandomSeed: function (event) {
		var runtimeOptions = this.state.runtimeOptions;
		runtimeOptions[this.state.runtimeOptionNumber].randomSeed = event.targe.value;
		this.setState({ runtimeOptions: runtimeOptions});
	},
	onChangeTimeout: function (event) {
		var runtimeOptions = this.state.runtimeOptions;
		runtimeOptions[this.state.runtimeOptionNumber].timeout = event.targe.value;
		this.setState({ runtimeOptions: runtimeOptions});
	}
});

module.exports = RuntimeOptionModal;