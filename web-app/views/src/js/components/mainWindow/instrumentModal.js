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
							<div class="radio leftFloat flexDisplay">
								<label class="spaceLeft"><input type="radio" name="optradio"/>Hardware Injection</label>
								<label class="spaceLeft"><input type="radio" name="optradio"/>Software Injection</label>
							</div>
							<button class="rightFloat">Reset Profile</button>
						</div>
						<div><p class="boldFont">Compile Option: </p></div>
						<div class="rowContainer">
							<p class="spaceLeft leftFloat">Instruction Selection Method </p>
							<div class="radio radio leftFloat flexDisplay">
								<label class="spaceLeft"><input type="radio" name="optradio"/>Instruction Type</label>
								<label class="spaceLeft"><input type="radio" name="optradio"/>Custom Instruction Selector</label>
							</div>	
						</div>
						<div class="rowContainer">
							<div class="btn-group rightFloat">
								<button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
									---Select--- <span class="caret"></span>
								</button>
								<ul class="dropdown-menu">
									<li><a > </a></li>
								</ul>
							</div>
						</div>
						<div class="rowContainer">
							<div class="rowContainer">
								<Checkbox readOnly class="rightFloat">
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
						<div class="rowContainer">
							<p class="spaceLeft leftFloat">Register Selection Method</p>
							<div class="radio rightFloat flexDisplay">
								<label class="spaceLeft"><input type="radio" name="optradio"/>Register Location</label>
								<label class="spaceLeft"><input type="radio" name="optradio"/>Custom Register Selector</label>
							</div>	
						</div>
						<div class="rowContainer">
							<div class="rightFloat">
								<FormGroup controlId="formControlsSelect">
									<FormControl componentClass="select" placeholder="select">
									<option value="notSpecified">---Select---</option>
									</FormControl>
								</FormGroup>
							</div>
							<div class="rightFloat registerSelectSpace">
								<FormGroup controlId="formControlsSelect">
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
							<div class="radio rightFloat flexDisplay">
								<label class="traceOptions"><input type="radio" name="optradio"/>No Trace</label>
								<label class="traceOptions"><input type="radio" name="optradio"/>Full Trace</label>
								<label class="traceOptions"><input type="radio" name="optradio"/>Limited Trace</label>
							</div>
						</div>
						<div class="rowContainer">
							<div class="rightFloat flexDisplay">
								<label>Max Trace Count</label>
								<input type="text" class="maxTraceCount"></input>
							</div>
							<div class="rightFloat fullTraceOptions">
								<Checkbox readOnly>Backward</Checkbox>
								<Checkbox readOnly>Forward</Checkbox>
							</div>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<Button>Instrument</Button>
					</Modal.Footer>
				</Modal>
			</div>
		);
	}
});

module.exports = InstrumentModal;