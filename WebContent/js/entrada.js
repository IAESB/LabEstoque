
function removeEntrada(id)
{
    $.post("/entrada/excluir", {id: id}, function(result)
    {
        if(result == "ok")
            document.location.href = "/entrada";
        else
            alert(result);
    });
}

function mostrarEntrada(id) 
{	
	mostrarNovaEntrada();
    $("#criarCancelar").html("Voltar");
    var formEntrada = document.querySelector("#formNovaEntrada");
    desabilitaEdicao(formEntrada);
    
    var btAlterar = formEntrada.querySelector("#btAlterar");
    btAlterar.innerHTML="Alterar";
    btAlterar.onclick = function(event){
        if(btAlterar.innerHTML=="Alterar"){
            btAlterar.innerHTML="Cancelar";
            abilitaEdicao(formEntrada);
            formEntrada.setAttribute("action", "/entrada/alterar?id="+id);
        }else{
            desabilitaEdicao(formEntrada);
            btAlterar.innerHTML="Alterar";
            formEntrada.setAttribute("action", "/entrada/salvar");
        }
    }
    var btExcluir = formEntrada.querySelector("#btExcluir");
    btExcluir.onclick = function(event){
        removeEntrada(id);
    }
    
	$.get("/entrada/get", { id: id }, function(dados) 
	{
		formEntrada.querySelector("input[name=fornecedor]").value = dados.fornecedor;
		formEntrada.querySelector("input[name=data]").value = dados.data.substr(0, 10);
		formEntrada.querySelector("textarea").value = dados.anotacao;
		for (var i=0; i<dados.materiais.length; i++) {
            var linha = formEntrada.querySelector("#tabelaMateriais tbody tr:last-child");
            linha.querySelector("input[name=material]").value = dados.materiais[i].nome;
            linha.querySelector("input[name=quantidade]").value = dados.materiais[i].quantidade;
            linha.querySelector("input[name=validade]").value = dados.materiais[i].validade;
            linha.querySelector("input[name=lote]").value = dados.materiais[i].lote;
            linha.querySelector("input[name=valor]").value = dados.materiais[i].valor;
            
            maisUmMaterial();
		}
        formEntrada.querySelector("#tabelaMateriais tbody tr:last-child").remove();
	},
	"json"
	);
}

function abilitaEdicao(formEntrada)
{
    var fields =  formEntrada.querySelectorAll("input");
    for(var i=0; i<fields.length; i++)
        fields[i].removeAttribute("disabled");
    var buttons = formEntrada.querySelectorAll("fieldset button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = ""; 
    
    formEntrada.querySelector("#salvar").style.display = ""; 
    formEntrada.querySelector("textarea").removeAttribute("disabled");
}

function desabilitaEdicao(formEntrada)
{
    var fields =  formEntrada.querySelectorAll("input");
    for(var i=0; i<fields.length; i++)
        fields[i].setAttribute("disabled", true);
    var buttons = formEntrada.querySelectorAll("fieldset button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "none";            

    formEntrada.querySelector("#salvar").style.display = "none"; 
    formEntrada.querySelector("textarea").setAttribute("disabled", true);
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
		$("#criarCancelar").show();
		$("#tabelaEntrada").show();	
        var linhas = document.querySelectorAll("#tabelaMateriais tbody tr");
        for(var i=1; i<linhas.length; i++)
            linhas[i].remove();
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
	var tr = document.querySelectorAll("#tabelaMateriais tbody tr");
	for(var j=0; j<tr.length; j++)
	{
		var idMaterial;
		var inputs = tr[j].querySelectorAll("input");
		for(var i=0; i<inputs.length; i++)
		{
			var input = inputs[i];
			var name = input.getAttribute("name");
			if (name=="material")
			{
				var opt = $("#tabelaMateriais option[value='"+input.value+"']");
				idMaterial = opt.prop('label');
				if(!idMaterial)
					idMaterial = "novo"+j;
			}
			input.setAttribute("name", name+"_"+idMaterial); 
		}
	}
}

