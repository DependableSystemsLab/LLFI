var React = require('react');
var Modal = require('react-bootstrap').Modal;

var InstrumentModal = React.createClass({

	getInitialState() {
		return { showModal: false };
	},

	close() {
		this.setState({ showModal: false });
	},

	open() {
		this.setState({ showModal: true });
	},

	render: function() {
		return (
			<div id="InstrumentModalID" onClick={this.open}>
				<Modal show={this.state.showModal} onHide={this.close}>
					<Modal.Header closeButton>
						<Modal.Title>Instrument</Modal.Title>
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
						<form>
							<div class="form-group">
								<select multiple class="form-control" id="sel2">
									<option>ret-(ReturnInst)</option>
									<option>br-(BranchInst)</option>
									<option>switch-(SwitchInst)</option>
									<option>indirectbr-(IndirectBrInst)</option>
									<option>invoke-(InvokeInst)</option>
								</select>
							</div>
						</form>
						<br/>
						<div>
							<h2>Register Selection Method</h2>
							<div class="radio">
								<label><input type="radio" name="optradio"/>Register Location</label>
								<label><input type="radio" name="optradio"/>Custom Register Selector</label>
							</div>	
						</div>
						<div>
							<div class="btn-group">
								<button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
									---Select--- <span class="caret"></span>
								</button>
								<ul class="dropdown-menu">
									<li><a > </a></li>
								</ul>
							</div>
							<div class="btn-group">
								<button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
									---Select--- <span class="caret"></span>
								</button>
								<ul class="dropdown-menu">
									<li><a > </a></li>
								</ul>
							</div>
						</div>
						<br/>
						<div>
							<h2>Inject Trace</h2>
							<div class="radio">
								<label><input type="radio" name="optradio"/>No Trace</label>
								<label><input type="radio" name="optradio"/>Full Trace</label>
								<label><input type="radio" name="optradio"/>Limited Trace</label>
							</div>
						</div>
					</Modal.Body>
					<Modal.Footer>
						<button onClick={this.close}>Close</button>
					</Modal.Footer>
				</Modal>
			</div>
		);
	}
});

module.exports = InstrumentModal;