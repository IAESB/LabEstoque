function mostrarSaida(idSaida)
{
    mostrarNovaSaida();
    $("#criarCancelar").html("Voltar");
    var fields = document.querySelectorAll("#formNovaSaida input, #formNovaSaida select");
    for(var i=0; i<fields.length; i++)
        fields[i].setAttribute("disabled", true);
    var buttons = document.querySelectorAll("#formNovaSaida button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "none";
    
    $.getJSON("/saida/get", { id: idSaida }, function(saida) 
              {
        document.querySelector("#formNovaSaida input[name=data]").value = saida.data.substr(0, 10);
        
        var opt = document.querySelector("#laboratorios option[label='"+saida.laboratorio+"'");
        document.querySelector("#formNovaSaida input[name=laboratorio]").value = opt.value;
        
        opt = document.querySelector("#solicitantes option[label='"+saida.solicitante+"'");
        document.querySelector("#formNovaSaida input[name=solicitante]").value = opt.value;
        
        for(var i=0; i<saida.materiais.length; i++)
        {
            var mat = saida.materiais[i];
            var linha = document.querySelector("#tabelaMateriais tbody tr:last-child");
            linha.querySelector("select[name=materiais]").value = mat.material;
            linha.querySelector("input[name=quantidade]").value = mat.quantidade;
            
            maisUmMaterial();
        }
        document.querySelector("#tabelaMateriais tbody tr:last-child").remove();
    },
    "json"
    );
}

function voltaInicioSaida() 
{	  
    $("#criarCancelar").html("Nova Saida");
	$(".saida").hide();
    $("#tabelaSaida").show();
    var fields = document.querySelectorAll("#formNovaSaida input, #formNovaSaida select");
    for(var i=0; i<fields.length; i++){
        fields[i].removeAttribute("disabled");
        fields[i].value="";
    }
    var buttons = document.querySelectorAll("#formNovaSaida button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "";
    
    var linhas = document.querySelectorAll("#tabelaMateriais tbody tr");
    for(var i=1; i<linhas.length; i++)
    {
        linhas[i].remove();
    }
}

function mostrarNovaSaida()
{
	var btm = $("#criarCancelar");
	if(btm.html()=="Nova Saida"){
		btm.html("Cancelar");
		$(".saida").hide();
		$("#formNovaSaida").show();	
	}
	else {		
		voltaInicioSaida();	
	}
}

function validarSalvarSaida()
{    
	var idMaterial =-1;
    var inputs = $("#tabelaMateriais :input");
    for(i in inputs)
    {
        var input = inputs[i];
        var name = input.getAttribute("name");
        if (name=="materiais")
        {            
            idMaterial = input.options[input.selectedIndex].value;
            input.remove();
        }
        else if(!name)
            input.remove();
        else{
            name = input.getAttribute("name");
            input.setAttribute("name", name+"_"+idMaterial);
        }
    }
    
    if(idMaterial>0)
	   return true;
    
    return false;
}