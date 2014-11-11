function urlParameters () {
    var result = {};
    result.length = 0;

    var params = window.location.search.split(/\?|\&/);

    params.forEach( function(it) {
        if (it) {
            var param = it.split("=");
            result[param[0]] = decodeURI( param[1] ).replace('+', ' ');
            result.length++;
        }
    });

    return result;
}

$(document).ready( function() 
{	
    var path = 	window.location.pathname;
    var end = path.indexOf('/', 1);
    if(end>0)
        path = path.substring(0, end);
	$("a[href='"+path+"']").parent().addClass('active');	
});
