var React = require('react');
var ReactDOM = require('react-dom');
var Header = require('./header');
var Body = require('./body');
var Footer = require('./footer');
var Layout = React.createClass({
  render: function() {
    return (
      <div id = "Home">
        <Header/>
        <Body/>
        <Footer/>
      </div>
    );
  }
});

module.exports = Layout;