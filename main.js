;(function() {

    "use strict";

    var osc = require('oscsocket');

    var PLUGIN_ID = require("./package.json").name;
    var MENU_ID = "fp";
    
    var _generator;

    var socket = new osc.OSCSocket();
    socket.bind();

    function init(generator) {
        _generator = generator;
        _generator.onPhotoshopEvent("imageChanged", onImageChanged);
	}

	function onImageChanged(event) {
		//console.log(event);
		_generator.evaluateJSXFile("../../plugins/PSGenILDA/generate.jsx").then(onSuccess, onError)
	}
    
    function onSuccess(event){
	    //console.log("success",event);
	    var msg = new osc.OSCMessage( "/path ," + event.types + " " + event.points );
	    socket.send( msg, 10001 );
	}

    function onError(event){
	    console.log("error",event);
	}

    exports.init = init;

}).call(this);