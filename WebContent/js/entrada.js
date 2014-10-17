
function mostrarEntrada(id) 
{	
	$(".entrada").hide();
	$("#mostrarEntrada").show();
	$("#tableMostraEntrada tbody").remove();
	$("#tableMostraEntrada").append("<tbody></tbody>");
	$.get("/entrada/get", { id: id }, function(dados) 
	{
		$("#fornecedor").prop('value', dados.fornecedor);
		$("#data").prop('value', dados.data.substr(0, 10));
		for (var i in dados.materiais) {
			var tr = "<tr><td>"+dados.materiais[i].nome+"</td>\
						 <td>"+dados.materiais[i].quantidade+"</td>\
						 <td>"+dados.materiais[i].validade.substr(0, 10)+"</td>\
						 <td>"+dados.materiais[i].lote+"</td>\
						 <td>"+dados.materiais[i].valor+"</td></tr>";
			
			$("#tableMostraEntrada tbody").append(tr);
		}
	},
	"json"
	);
}

function inicioEntrada() 
{
	$(".entrada").hide();
	$("#tabelaEntrada").show();		
}

function mostrarNovaEntrada(btm)
{
	$('div').find('input').prop('disabled', false);
	var form = $(".formNovaEntrada");
	if(form.is(':visible')){
		$(".entrada").hide();
		$("#criarCancelar").html("Criar Entrada");
		$("#tabelaEntrada").show();		
	}
	else{	
		$(".entrada").hide();
		$("#criarCancelar").html("Cancelar");		
		form.show();
		$("input[name='data']").focus();
	}
}


function validarSalvarEntrada() 
{
    var idMaterial =-1;
    var cont = 1;
	$("#tabelaMateriais input").each(function( ) 
	{
        var input = $( this );
        var name = input.prop("name");
        if (name=="material")
        {
            idMaterial = $("#tabelaMateriais option[value='"+input.val()+"']").prop('label');
            if(!idMaterial)
                idMaterial = "novo"+cont;
        }
        input.prop("name", name+"_"+idMaterial);  
        cont++;
	});
	
    if(idMaterial>0)
        return true;

    return false;			
}

