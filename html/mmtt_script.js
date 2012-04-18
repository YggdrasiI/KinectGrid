function myField(myoptions){
	ret = function(options) {
		// Return a new button element that has all options that
		// don't have a registered subscriber as attributes
		//alert(options);
		ret = $("<p>");
		//alert(options.toSource());
		//alert("Min? "+options.value);
		inputfield = $('<input id="'+options.id+'" readonly="readonly" value="'+options.val+'" size="6" />');//.dform('attr', options)
		//inputfield.click( function(event){ alert("Foo\n"+event.target.id) });
		m1 = $('<input type="button" value="---" />');
		m1.click( function(event){ myoptions.change(options.id,options.min,options.max,-options.diff); });
		m2 =  $('<input type="button" value="-" />');
		m2.click( function(event){ myoptions.change(options.id,options.min,options.max,-options.diff/10.0); });
		m3 =  $('<input type="button" value="-" />');
		m3.click( function(event){ myoptions.change(options.id,options.min,options.max,-options.diff/100.0); });

		p1 =  $('<input type="button" value="+" />');
		p1.click( function(event){ myoptions.change(options.id,options.min,options.max, options.diff/100.0); });
		p2 =  $('<input type="button" value="++" />');
		p2.click( function(event){ myoptions.change(options.id,options.min,options.max, options.diff/10.0); });
		p3 =  $('<input type="button" value="+++" />');
		p3.click( function(event){ myoptions.change(options.id,options.min,options.max, options.diff); });

		propName = $('<span>'+options.id+': </span>');
		propName.addClass("propName");

		ret.append( inputfield ); 
		ret.prepend(m3);
		ret.prepend(m2);
		ret.prepend(m1);
		ret.append(p1);
		ret.append(p2);
		ret.append(p3);
		ret.prepend(propName);
		return  ret;
	}
	return ret;
}

intoptions = {}
intoptions.change = changeInt;
doubleoptions = {}
doubleoptions.change = changeDouble;

$.dform.addType("doubleField", myField(doubleoptions) );
$.dform.addType("intField", myField(intoptions) );

$.dform.subscribe({
	"val" : function (options) {
			//alert("val "+options.toSource()+"\n"+options);
			//$(this).attr("value", ""+options);
			//$(this).val("Text"+options);
		},
	"min" : function (options, type) {
			/*
			$(this).click(function(event){
  		   alert("Decrease Value "+this.id);
		   });*/
		}
});



function changeDouble(id,min,max,diff){
	//update displayed value
	o = document.getElementById(id);
 	val = Math.min(Math.max(min,Number(o.value)+diff),max);
	//round to cut rounding errors
	val = Math.round( val*1E6)/1E6;
 	o.value = val;

	//modifyJson obj.
	modifyJson(id,val);

	//send altered obj. to server
	send("json?actionid=0","settingKinect="+JSON.stringify(json_kinect));
}

function changeInt(id,min,max,diff){
	//update displayed value
	o = document.getElementById(id);
 	val =  Math.min(Math.max(min,Math.round(Number(o.value)+diff)),max);
 	o.value = val;

	//modifyJson obj.
	modifyJson(id,val);

	//send altered obj. to server
	send("json?actionid=0","settingKinect="+JSON.stringify(json_kinect));
}

//modifiy children of html node (no rekursion implemented)
function modifyJson(id,val){
	$.each(	json_kinect.html, function(index,v){
		if(v.id==id){ v.val=val; }
		});
}

//send complete json struct
function send(url,val){
	$.post(url, val , function(data){
		if( data == "reload" ){
			alert("Reload Page");
			window.location.reload();
		}else{
			//some other reaction...
		}
	});

	return true;
}

function loadConfig(){
	filename = document.getElementById("configFilename").value;
	send("json?actionid=1","filename="+filename);
}

function saveConfig(){
	filename = document.getElementById("configFilename").value;
	send("json?actionid=2","filename="+filename);
}

function deepCopy(p,c) {
	var c = c||{}; for (var i in p) {
		if (typeof p[i] === 'object') {
			c[i] = (p[i].constructor === Array)?[]:{};
			deepCopy(p[i],c[i]);
		} else c[i] = p[i];
	}
	return c;
} 
