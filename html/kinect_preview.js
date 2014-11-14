function utf8_to_b64( str ){
	return window.btoa(unescape(encodeURIComponent( str )));
}

function b64_to_utf8( str ){
	return decodeURIComponent(escape(window.atob( str )));
}

function reloadImage(manual){

	if(manual){
		//clear pending refresh
		window.clearInterval(refreshIntervall);
	}

	if( !manual && $("#previewRefresh").prop("checked") != true ) return true;

	var scale = $("#previewScale").prop("zoomval");
	var d = new Date();
	if( isNaN(scale) ) scale = 50;

	var newImg = new Image();
	newImg.onload = function(){
		if( newImg.width < 2 ){
			if(manual) $("#info").empty().fadeIn(0).append("No new image").fadeOut(1000);
		}else{
			if(manual) $("#info").empty().fadeIn(0).append("Load new image").fadeOut(1000);
			$("#previewImg").empty().append($(newImg));
		}
	};

	newImg.src = "preview.jpg?scale="+scale+"&force=1#"+d.getTime();

	if(manual){
		refreshIntervall = window.setInterval("reloadImage(false)", 2*500);
	}

	return true;
}


$(function(){

//add event handler to update zoom factor
	scaleSelect = $("#previewScale");
	scaleSelect.prop("zoomval", scaleSelect.val());
	scaleSelect.change( function(event){
		scaleSelect.prop("zoomval", scaleSelect.val());
	});

});

refreshIntervall = window.setInterval("reloadImage(false)", 500);
