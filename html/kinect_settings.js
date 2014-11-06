var json_kinect = {{ONION_JSON_KINECT}};    

json_messages = {
	"kind" : "B9CreatorMessages",
	"html" : [{
		"type" : "messagesField",
		"id" : "serialMessages",
		"messages" : []
	}]
};


$(function(){

		create_fields(json_kinect);
		create_fields(json_messages);
		
		//create_jobFileList();
		//create_jobTimingStates();

});


/* Alt
$(function(){
		//Add hidden input field stub and create form
		a = deepCopy(json_kinect);

		//b ={"name":"json","id":"json","type":"text","size":"100","value":JSON.stringify(json_kinect)};
		//a.html[a.html.length] = b;

    $("#settingKinectForm").dform(a);
});
*/

//refreshIntervall = window.setInterval("refresh()", 1000);

