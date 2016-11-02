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
			runtimeOptions: [{injectionType: "bitflip"}],
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
							<input id="numberOfRuns" class="runtimeInputs" type="number" onChange={this.onChangeNumberofRuns} min={1}></input>
						</div>
						<div>
							<button>{"<"}</button>
							<button class="rightFloat">{">"}</button>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Random Seed</label>
							<input id="randomSeed" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeRandomSeed}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>TimeOut(ms)</label>
							<input id="timeout" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeTimeout}></input>
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
							<input id="numberOfRuns" class="runtimeInputs" type="number" min={1} onChange={this.onChangeNumberofRuns}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Type<span class="redColor">*</span></label>
							<div class="runtimeInputs">
								<FormGroup controlId="injectionType">
									<FormControl componentClass="select" placeholder="select" onChange={this.onChangeInjectionType}>
									<option value="bitflip">bitflip</option>
									<option value="stuck_at_0">stuck_at_0</option>
									<option value="stuck_at_1">stuck_at_1</option>
									</FormControl>
								</FormGroup>
							</div>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Cycles</label>
							<input id="injectionCycles" class="runtimeInputs" type="number" placeholder="max:-1" onChange={this.onChangeInjectionCycles}></input>
						</div>
						<div>
							<button onClick={this.previousRun}>{"<"}</button>
							<button class="rightFloat" onClick={this.nextRun}>{">"}</button>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Index</label>
							<input id="injectionIndex" class="runtimeInputs" type="number" placeholder="max:34" onChange={this.onChangeInjectionIndex}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Register Index</label>
							<input id="injectionRegisterIndex" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeInjectionRegisterIndex}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Fault Injection Bit</label>
							<input id="injectionBit" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeInjectionBit}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>Random Seed</label>
							<input id="randomSeed" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeRandomSeed}></input>
						</div>
						<div class="runtimeContainer flexDisplay">
							<label>TimeOut(ms)</label>
							<input id="timeout" class="runtimeInputs" type="text" placeholder="null" onChange={this.onChangeTimeout}></input>
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
		this.runtimeOptionChange("numberOfRuns", event.target.value);
	},
	onChangeRandomSeed: function (event) {
		this.runtimeOptionChange("randomSeed", event.target.value);
	},
	onChangeTimeout: function (event) {
		this.runtimeOptionChange("timeout", event.target.value);
	},
	onChangeInjectionType: function (event) {
		this.runtimeOptionChange("injectionType", event.target.value);
	},
	onChangeInjectionCycles: function (event) {
		this.runtimeOptionChange("injectionCycles", event.target.value);
	},
	onChangeInjectionIndex: function (event) {
		this.runtimeOptionChange("injectionIndex", event.target.value);
	},
	onChangeInjectionRegisterIndex: function (event) {
		this.runtimeOptionChange("injectionRegisterIndex", event.target.value);
	},
	onChangeInjectionBit: function (event) {
		this.runtimeOptionChange("injectionBit", event.target.value);
	},
	runtimeOptionChange: function (filedName, value) {
		var runtimeOptions = this.state.runtimeOptions;
		runtimeOptions[this.state.runtimeOptionNumber][filedName] = value;
		this.setState({ runtimeOptions: runtimeOptions});
	},
	previousRun: function () {
		var previousRunNumber = this.state.runtimeOptionNumber - 1;
		if (previousRunNumber < 0) {
			return;
		}
		this.loadRunOption(previousRunNumber);
		this.setState({runtimeOptionNumber: previousRunNumber});
	},
	nextRun: function () {
		var nextRunNumber = this.state.runtimeOptionNumber + 1;
		var runtimeOptions = this.state.runtimeOptions;
		// If the previous run has not specifed the required fields, do not create a new run
		if (!this.isRequiredFilled(runtimeOptions[nextRunNumber]) && !this.isRequiredFilled(runtimeOptions[this.state.runtimeOptionNumber])) {
			return;
		}

		if (!runtimeOptions[nextRunNumber]) {
			// Add a new run option
			runtimeOptions[nextRunNumber] = {injectionType: "bitflip"};
		}
		this.loadRunOption(nextRunNumber);
		this.setState({ runtimeOptions: runtimeOptions, runtimeOptionNumber: nextRunNumber});
	},
	loadRunOption: function (runNumber) {
		var runOption = this.state.runtimeOptions[runNumber];
		$("#numberOfRuns").val(runOption.numberOfRuns);
		$("#randomSeed").val(runOption.randomSeed);
		$("#timeout").val(runOption.timeout);
		if(runOption.injectionType) {
			$("#injectionType").val(runOption.injectionType);
		} else {
			$("#injectionType").val("bitflip");
		}
		$("#injectionCycles").val(runOption.injectionCycles);
		$("#injectionIndex").val(runOption.injectionIndex);
		$("#injectionRegisterIndex").val(runOption.injectionRegisterIndex);
		$("#injectionBit").val(runOption.injectionBit);

	},
	isRequiredFilled: function (obj) {
		if (!obj) return false;
		if (obj.numberOfRuns) return true;
		return false;
	}
});

module.exports = RuntimeOptionModal;