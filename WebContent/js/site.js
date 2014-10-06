
$(document).ready( function() {
	$('.top-nav ul li').click(function(){
		$('.top-nav ul li').removeClass('active');
		$(this).addClass('active');	});

	$('.top-nav ul li a').on("click", function (e) {
    	e.preventDefault();
    	var dest = this.href.split("/");
    	dest = "#"+dest[dest.length -1];
    	window.location.href = dest;
    	$("#conteudo").load(this.href, function( response, status, xhr ) {
		if ( status == "error" )
			$("#conteudo").load("404.html");
		});
	});
});
