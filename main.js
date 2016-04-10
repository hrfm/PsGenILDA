;(function() {

    "use strict";

    var _generator;
    var PLUGIN_ID = require("./package.json").name;

    var osc    = require('oscsocket');
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
	    socket.send( msg, 22222 );
	}

    function onError(event){
	    console.log("error",event);
	}
    
    exports.init = init;

}).call(this);