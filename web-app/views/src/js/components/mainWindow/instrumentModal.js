var React = require('react');
var Modal = require('react-modal');

const customStyles = {
	content : {
		top                   : '50%',
		left                  : '50%',
		right                 : 'auto',
		bottom                : 'auto',
		marginRight           : '-50%',
		transform             : 'translate(-50%, -50%)'
	}
};


var InstrumentModal = React.createClass({

	getInitialState: function() {
		return { modalIsOpen: false };
	},

	openModal: function() {
		this.setState({modalIsOpen: true});
	},

	afterOpenModal: function() {
		// references are now sync'd and can be accessed.
		this.refs.subtitle.style.color = '#f00';
	},

	closeModal: function() {
		this.setState({modalIsOpen: false});
	},

	render: function() {
		return (
			<div id="InstrumentModalID" onClick={this.openModal}>
				<Modal
				isOpen={this.state.modalIsOpen}
				onAfterOpen={this.afterOpenModal}
				onRequestClose={this.closeModal}
				style={customStyles} >

					<h2 ref="subtitle">Hello</h2>
					<button onClick={this.closeModal}>close</button>
					<div>I am a modal</div>
					<form>
					<input />
					<button>tab navigation</button>
					<button>stays</button>
					<button>inside</button>
					<button>the modal</button>
					</form>
				</Modal>
			</div>
		);
	}
});

module.exports = InstrumentModal;