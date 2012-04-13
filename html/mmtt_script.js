$.dform.addType("doubleField", function(options) {
    // Return a new button element that has all options that
    // don't have a registered subscriber as attributes
//alert(options);
		ret = $("<p>");
//alert(options.toSource());
		//alert("Min? "+options.value);
		inputfield = $('<input id="'+options.id+'" readonly="readonly" value="'+options.val+'" size="6" />');//.dform('attr', options)
		//inputfield.click( function(event){ alert("Foo\n"+event.target.id) });
		m1 = $('<input type="button" value="---" />');
		m1.click( function(event){ change(options.id,options.min,options.max,-options.diff); });
		m2 =  $('<input type="button" value="-" />');
		m2.click( function(event){ change(options.id,options.min,options.max,-options.diff/10.0); });
		m3 =  $('<input type="button" value="-" />');
		m3.click( function(event){ change(options.id,options.min,options.max,-options.diff/100.0); });

		p1 =  $('<input type="button" value="+" />');
		p1.click( function(event){ change(options.id,options.min,options.max, options.diff/100.0); });
		p2 =  $('<input type="button" value="++" />');
		p2.click( function(event){ change(options.id,options.min,options.max, options.diff/10.0); });
		p3 =  $('<input type="button" value="+++" />');
		p3.click( function(event){ change(options.id,options.min,options.max, options.diff); });

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
});

$.dform.subscribe({
	"val" : function (options) {
			//alert("val "+options.toSource()+"\n"+options);
			//$(this).attr("value", ""+options);
			$(this).val("Text"+options);
		},
	"min" : function (options, type) {
			/*
			$(this).click(function(event){
  		   alert("Decrease Value "+this.id);
		   });*/
		}
});


function change(id,min,max,diff){
	//update displayed value
	o = document.getElementById(id);
 	val = Math.min(Math.max(min,Number(o.value)+diff),max);
 	o.value = val;

	//modify json-object, too.
	$.each(	json_kinect.html, function(index,v){
		if(v.id==id){ v.val=val; }
		});

	/*
	//update hidden form field
	//document.getElementById("json").value = json_kinect.toSource().slice(1,-1);// toSource is bad
	document.getElementById("json").value = JSON.stringify(json_kinect);

 //submit parent form of object o. Only json-object will be attend by the server
	while( o.parentNode != null && o.parentNode.tagName != "BODY"){
		if( o.tagName == "FORM"){
			o.submit();
		}
		o = o.parentNode;
  }
 */
	//send complete json struct
	$.post('json', json_kinect , function(data){
		if( data == "reload" ){
			window.location.reload();
		}else{
			//some other reaction...
		}
	});

	return true;
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
