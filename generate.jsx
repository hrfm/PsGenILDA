var docW = activeDocument.width.value;
var docH = activeDocument.height.value;

var gTop    = 0.0;
var gBottom = 1.0;
var gLeft   = 0.0;
var gRight  = 1.0;
var gDX = 1.0;
var gDY = -1.0;

function addPoint( arr, x, y ){
	arr.push( 1.0-(x/docW) );
	arr.push( 1.0-(y/docH) );
}

function mapPathCSV( target ){
	
	var types  = "";
	var points = [];

	for(var j=target.pathItems.length-1; 0<=j; j-- ){
		var pItems = target.pathItems[j];
		types += "s";
		points.push("f");
		for( var k=0; k<pItems.subPathItems.length; k++ ){
			var pp = pItems.subPathItems[k].pathPoints;
			types += "s";
			points.push("l");
			for(var i=0; i<pp.length; i++){
				var p = pp[i];
				// --- Anchor
				types += "ff";
				addPoint( points, p.anchor[0], p.anchor[1] );
				// --- leftDirection
				types += "ff";
				addPoint( points, p.leftDirection[0], p.leftDirection[1] );
				// --- rightDirection
				types += "ff";
				addPoint( points, p.rightDirection[0], p.rightDirection[1] );
			}
		}
	}
	
	return '{' +
		'"types" :"' + types + '",' +
		'"points":"' + points.join(" ") + '"' +
	'}';

}

(function(){
	return mapPathCSV( activeDocument );
})();