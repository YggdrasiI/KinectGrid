/* Wait period after image loading in ms.
 * Note that the complete waitingtime is RELOAD_MS + [image download time].
 * The second part dominates if the server can not provide the images in realtime.
*/
RELOAD_MS = 1000

/* Number of skiped image fetch calls if previous image fetch failed. */
OFFLINE_SKIP = 10
offline_skip = 0

/* Already set by json_settings_editor.js, but this script works standalone, too. */
if( typeof server_online == 'undefined' ) server_online = true;
if( typeof refreshTimeout_previewImage == 'undefined' ) refreshTimeout_previewImage = null; 

function utf8_to_b64( str ){
	return window.btoa(unescape(encodeURIComponent( str )));
}

function b64_to_utf8( str ){
	return decodeURIComponent(escape(window.atob( str )));
}

function reloadImage(manual){
	//clear pending refresh
	window.clearTimeout(refreshTimeout_previewImage);

	if( !server_online && !manual ){
		if( offline_skip++ < OFFLINE_SKIP ){
			refreshTimeout_previewImage = window.setTimeout("reloadImage(false)", RELOAD_MS);
			return true;
		}else{
			offline_skip = 0;
		}
	}

	if( !manual && $("#previewRefresh").prop("checked") != true ){
		refreshTimeout_previewImage = window.setTimeout("reloadImage(false)", RELOAD_MS);
		return true;
	}

	var scaleIn = parseInt($("#previewScaleIn").prop("zoomval"));
	if( isNaN(scaleIn) ) scaleIn = 100;
	var scaleOut = parseInt($("#previewScaleOut").prop("zoomval"));
	if( isNaN(scaleOut) ) scaleOut = 100;
	var d = new Date();
	var newImg = new Image();

	newImg.onload = function(){
		server_online = true;
		window.clearTimeout(refreshTimeout_previewImage);
		refreshTimeout_previewImage = window.setTimeout("reloadImage(false)", RELOAD_MS);

		if( newImg.width < 2 ){
			if(manual) $("#info").empty().fadeIn(0).append("No new image").fadeOut(400);
		}else{
			newImg.width = newImg.naturalWidth*(scaleOut/100.0);
			newImg.height = newImg.naturalHeight*(scaleOut/100.0);
			if(manual) $("#info").empty().fadeIn(0).append("Load new image").fadeOut(400);
			$("#previewImg").empty().append($(newImg));
		}
	};
	newImg.src = "preview.image?scale="+scaleIn+"&force=1#"+d.getTime();

	setTimeout(
			function()
			{
			if ( !newImg.complete || !newImg.naturalWidth )
			{
			server_online = false;
			// replace by black pixel 
			newImg.src = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNg+A8AAQIBANEay48AAAAASUVORK5CYII="; 
			window.clearTimeout(refreshTimeout_previewImage);
			refreshTimeout_previewImage = window.setTimeout("reloadImage(false)", RELOAD_MS);
			}
			},
			1000
			);

	return true;
}


$(function(){

//add event handler to update zoom factors
	scaleSelectIn = $("#previewScaleIn");
	scaleSelectIn.prop("zoomval", scaleSelectIn.val());
	scaleSelectIn.change( function(event){
		scaleSelectIn.prop("zoomval", scaleSelectIn.val());
	});

	scaleSelectOut = $("#previewScaleOut");
	scaleSelectOut.prop("zoomval", scaleSelectOut.val());
	scaleSelectOut.change( function(event){
		scaleSelectOut.prop("zoomval", scaleSelectOut.val());

		//Update current image size, too.
		var scaleOut = parseInt(scaleSelectOut.prop("zoomval"));
		if( isNaN(scaleOut) ) scaleOut = 100;
		var curImg = $("#previewImg img").get(0);
		curImg.width = curImg.naturalWidth*(scaleOut/100.0);
		curImg.height = curImg.naturalHeight*(scaleOut/100.0);
	});

});

refreshTimeout_previewImage = window.setTimeout("reloadImage(false)", RELOAD_MS + 3000);
