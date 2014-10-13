
function mostrarNovaEntrada(elem)
{
	$("#tabelaEntrada").toggle();
	var form = $(".formNovaEntrada");
	form.toggle();
	$("input[name='data']").focus();
	if(form.is(':visible'))
		elem.innerHTML = "Cancelar";
	else 
		elem.innerHTML = "Criar Entrada";
}

function maisUmMaterial()
{
	var novaLinha = $("#linhaMaterial").clone();
	novaLinha.attr("id","");
	novaLinha.find(':input').val('').end();
	$("#tabelaMateriais").append(novaLinha);
	novaLinha.find(':input:first').focus();
	novaLinha.find(':button').prop("disabled",false);
}

function validarSalvarEntrada() {
	var datalist = $("#tabelaMateriais datalist:last");
	var erros=0;
	var inputRemove = new Array();
	var idMaterial;
	var data = $("input[name=data]");
	if (!data.val()){
		data.addClass("invalido");
  		erros++;	
	}
	$("#tabelaMateriais input").each(function( ) 
	{
  			var input = $( this );
  			input.removeClass();
  			var name = input.prop("name");
  			if (name=="material")
  			{
  				inputRemove.push(input);
  				idMaterial = datalist.find("option[value='"+input.val()+"']").html();
  			}
  			if ((name=="material" || name=="quantidade") && !input.val())
  			{
  				input.addClass("invalido");
  				erros++;
  			}
  			input.prop("name2", name+"_"+idMaterial);  	
	});
	
	if (erros>0)
		return false;
	else{
		$("#tabelaMateriais input").each(function( index )
		{
			var input = $( this );
			if(input.prop("name")=="material")
				input.remove();
			else
				input.prop("name", input.prop("name2") );
		});
	}	
	return true;			
}

function removeMaterial(elemento) {
	var row = elemento.parentNode.parentNode;
	row.remove();
}