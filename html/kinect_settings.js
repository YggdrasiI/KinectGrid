//json_kinect = {{ONION_JSON_KINECT}};    

json_messages = {
	"kind" : "KinectMessages",
	"html" : [{
		"type" : "messagesField",
		"id" : "serialMessages",
		"messages" : []
	}]
};

/*
$(function(){
		
	setTimeout(function(){
		send("settings","",
			function(data){
				json_kinect = JSON.parse(data);//change global var
				create_fields(json_kinect);
			}
			);
		//create_fields(json_kinect);
		create_fields(json_messages);
		//create_jobFileList();
		//create_jobTimingStates();
	}, 1000);

});
*/


//refreshTimeout = window.setTimeout("refresh()", 1000);

//=====================================
json_kinect = null;
refreshTimeout = null;
server_online = true;

