var React = require('react');
var Modal = require('react-bootstrap').Modal;
var FormGroup = require('react-bootstrap').FormGroup;
var FormControl = require('react-bootstrap').FormControl;
var Checkbox = require('react-bootstrap').Checkbox;
var Button = require('react-bootstrap').Button;
var ControlLabel = require('react-bootstrap').ControlLabel;

var InstrumentModal = React.createClass({

	getInitialState() {
		return { show: false };
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
			<div class="modal-container" id="InstrumentModalID" onClick={this.open}>
				<Modal {...this.props} bsSize="large" aria-labelledby="contained-modal-title-lg" onClick={this.open} show={this.state.show} onHide={this.close}>
					<Modal.Header closeButton>
						<Modal.Title id="contained-modal-title-lg">Instrument</Modal.Title>
					</Modal.Header>
					<Modal.Body>
						<div class="rowContainer">
							<p class="boldFont leftFloat">LLFI Configuration Parameters</p>
							<button class="rightFloat">Select Profile...</button>
						</div>
						<div class="rowContainer">
							
							<p class="boldFont leftFloat">Injection Type : </p>
							<div class="radio leftFloat flexDisplay" data-toggle="buttons">
								<label class="spaceLeft"><input type="radio" name="injectionMode" value="hardwareInjection" defaultChecked={true} onChange={this.injectionModeHandler}/>Hardware Injection</label>
								<label class="spaceLeft"><input type="radio" name="injectionMode" value="softwareInjection" onChange={this.injectionModeHandler}/>Software Injection</label>
							</div>
							<button class="rightFloat" disabled>Reset Profile</button>
						</div>
						<div><p class="boldFont">Compile Option: </p></div>
						<div class="rowContainer">
							<p class="spaceLeft leftFloat">Instruction Selection Method </p>
							<div id="instructionSelectionContainer" class="radio radio leftFloat flexDisplay" data-toggle="buttons">
								<label class="spaceLeft"><input type="radio" name="instructionSelection" value="defaultInstructionType" defaultChecked={true} onChange={this.intructionTypeHandler}/>Instruction Type</label>
								<label class="spaceLeft"><input type="radio" name="instructionSelection" value="customInstructionType" onChange={this.intructionTypeHandler}/>Custom Instruction Selector</label>
							</div>	
						</div>
						<div class="rowContainer">
							<FormGroup controlId="customSelector" class="rightFloat">
								<FormControl componentClass="select" disabled>
									<option value="notSpecified">---Select---</option>
								</FormControl>
							</FormGroup>
						</div>
						<div class="rowContainer">
							<div class="rowContainer">
								<Checkbox id="selectAllInstructionType" class="rightFloat">
									Include All
								</Checkbox>
							</div>
							<FormGroup controlId="formControlsSelectMultiple" class="rightFloat">
								<FormControl componentClass="select" multiple>
									<option value="ret-(ReturnInst)">ret-(ReturnInst)</option>
									<option value="br-(BranchInst)">br-(BranchInst)</option>
									<option value="switch-(SwitchInst)">switch-(SwitchInst)</option>
									<option value="indirectbr-(IndirectBrInst)">indirectbr-(IndirectBrInst)</option>
									<option value="invoke-(InvokeInst)">invoke-(InvokeInst)</option>
								</FormControl>
							</FormGroup>
						</div>
						<hr class="boldHr"/>
						<div id="registerSelectOptions" class="rowContainer">
							<p class="spaceLeft leftFloat">Register Selection Method</p>
							<div class="radio rightFloat flexDisplay" data-toggle="buttons">
								<label class="spaceLeft"><input type="radio" name="registerLocation" value="defaultRegisterLocation" defaultChecked={true} onClick={this.registerLocationHandler}/>Register Location</label>
								<label class="spaceLeft"><input type="radio" name="registerLocation" value="customRegisterLocation" onClick={this.registerLocationHandler}/>Custom Register Selector</label>
							</div>	
						</div>
						<div id="registerSelector" class="rowContainer">
							<div class="rightFloat">
								<FormGroup controlId="customRegister">
									<FormControl componentClass="select" placeholder="select" disabled>
									<option value="notSpecified">---Select---</option>
									</FormControl>
								</FormGroup>
							</div>
							<div class="rightFloat registerSelectSpace">
								<FormGroup controlId="defaultRegister">
									<FormControl componentClass="select" placeholder="select">
									<option value="notSpecified">---Select---</option>
									<option value="dstreg-(DESTINATION_REGISTER)">dstreg-(DESTINATION_REGISTER)</option>
									<option value="allsrcreg-(ALL_SOURCE_REGISTERS)">allsrcreg-(ALL_SOURCE_REGISTERS)</option>
									<option value="srcreg1-(SOURCE_REGISTER_1)">srcreg1-(SOURCE_REGISTER_1)</option>
									<option value="srcreg2-(SOURCE_REGISTER_2)">srcreg2-(SOURCE_REGISTER_2)</option>
									<option value="srcreg3-(SOURCE_REGISTER_3)">srcreg3-(SOURCE_REGISTER_3)</option>
									<option value="srcreg4-(SOURCE_REGISTER_4)">srcreg4-(SOURCE_REGISTER_4)</option>
									</FormControl>
								</FormGroup>
							</div>
						</div>
						<hr class="boldHr"/>
						<div class="rowContainer">
							<p class="spaceLeft leftFloat">Inject Trace</p>
							<div class="radio rightFloat flexDisplay" data-toggle="buttons">
								<label class="traceOptions"><input type="radio" value="noTrace" name="traceType" onChange={this.traceOptionHandler}/>No Trace</label>
								<label class="traceOptions"><input type="radio" value="fullTrace" name="traceType" defaultChecked={true} onChange={this.traceOptionHandler}/>Full Trace</label>
								<label class="traceOptions"><input type="radio" value="limitedTrace" name="traceType" onChange={this.traceOptionHandler}/>Limited Trace</label>
							</div>
						</div>
						<div class="rowContainer">
							<div class="rightFloat flexDisplay">
								<label>Max Trace Count</label>
								<input type="text" id="maxTraceCount" class="maxTraceCount" disabled></input>
							</div>
							<div class="rightFloat fullTraceOptions" data-toggle="buttons">
								<Checkbox id="backwardTrace" defaultChecked={true}>Backward</Checkbox>
								<Checkbox id="forwardTrace" defaultChecked={true}>Forward</Checkbox>
							</div>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<Button onClick={this.onClickInstrument}>Instrument</Button>
					</Modal.Footer>
				</Modal>
			</div>
		);
	},
	injectionModeHandler : function (event) {
		if (event.target.value === "softwareInjection") {
			this.enbaleSoftwareInjectionElements();
		} else if (event.target.value === "hardwareInjection") {
			this.enbaleHardwareInjectionElements();
		}
	},
	enbaleSoftwareInjectionElements : function () {
		$("#instructionSelectionContainer").hide();
		$("#customSelector").hide();
		$("#registerSelectOptions").hide();
		$("#registerSelector").hide();
	},
	enbaleHardwareInjectionElements: function () {
		$("#instructionSelectionContainer").show();
		$("#customSelector").show();
		$("#registerSelectOptions").show();
		$("#registerSelector").show();
	},
	traceOptionHandler: function (event) {
		if (event.target.value === "noTrace") {
			$("#maxTraceCount").prop("disabled", true);
			$("#backwardTrace").prop("disabled", true);
			$("#forwardTrace").prop("disabled", true);
		} else if (event.target.value === "fullTrace") {
			$("#maxTraceCount").prop("disabled", true);
			$("#backwardTrace").prop("disabled", false);
			$("#forwardTrace").prop("disabled", false);
		} else if (event.target.value === "limitedTrace") {
			$("#maxTraceCount").prop("disabled", false);
			$("#backwardTrace").prop("disabled", true);
			$("#forwardTrace").prop("disabled", true);
		}
	},
	intructionTypeHandler: function (event) {
		if (event.target.value === "customInstructionType") {
			$("#selectAllInstructionType").prop("disabled", true);
			$("#formControlsSelectMultiple").prop("disabled", true);
			$("#customSelector").prop("disabled", false);
		} else if (event.target.value === "defaultInstructionType") {
			$("#selectAllInstructionType").prop("disabled", false);
			$("#formControlsSelectMultiple").prop("disabled", false);
			$("#customSelector").prop("disabled", true);
		}
	},
	registerLocationHandler: function (event) {
		if (event.target.value === "defaultRegisterLocation") {
			$("#customRegister").prop("disabled", true);
			$("#defaultRegister").prop("disabled", false);
		} else if (event.target.value === "customRegisterLocation") {
			$("#customRegister").prop("disabled", false);
			$("#defaultRegister").prop("disabled", true);
		}
	},
	onClickInstrument: function (event) {
		// var data = {}
		// data.fileName = this.state.fileName;
		$.ajax({
			url: '/instrument',
			type: 'POST',
			data: "",
			processData: false,
			contentType: 'application/json',
			success: function(data){
				// fileUploadActions.addFiles(data);
				console.log("instrument success")
			}
		});
	}
});

module.exports = InstrumentModal;