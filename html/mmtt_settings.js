var json_kinect = {{ONION_JSON_KINECT}};    

$(function(){
		//Add hidden input field stub and create form
		a = deepCopy(json_kinect);

		b ={"name":"json","id":"json","type":"text","size":"100","value":JSON.stringify(json_kinect)};
		a.html[a.html.length] = b;

    $("#settingKinectForm").dform(a);
});

