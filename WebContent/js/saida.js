function selecionaMaterial(lote)
{
    var opt = document.querySelector("#materiais option[value='"+lote.value+"']");
    var idMat = opt.getAttribute("material-id") ;
    var material = lote.parentElement.querySelector("input[name=material]");
    material.value = idMat;
    var quantidade = lote.parentElement.parentElement.querySelector("input[name=quantidade]");
    quantidade.setAttribute("max", opt.getAttribute("qtd") );
    lote.setAttribute("lote-id", opt.getAttribute("lote-id"));
}

function desabilitaEdicao(formNovaSaida)
{
    var fields =  formNovaSaida.querySelectorAll("input");
    for(var i=0; i<fields.length; i++)
        fields[i].setAttribute("disabled", true);
    var buttons = formNovaSaida.querySelectorAll("fieldset button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "none";
    
    var lotes = formNovaSaida.querySelectorAll("input[name=lote]")
    for(var i=0; i<lotes.length; i++)
        lotes[i].setAttribute("list", "materiais");
    
    var btAlterar = formNovaSaida.querySelector("#btSalvar");
    btAlterar.style.display = "none";
        
}

function abilitaEdicao(formNovaSaida)
{
    var fields =  formNovaSaida.querySelectorAll("input");
    for(var i=0; i<fields.length; i++)
        fields[i].removeAttribute("disabled");
    
    var buttons = formNovaSaida.querySelectorAll("button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "inline"; 
    
    var lotes = formNovaSaida.querySelectorAll("input[name=lote]")
    for(var i=0; i<lotes.length; i++)
        lotes[i].setAttribute("list", "materiaisTodos");
}

function removerSaida(id)
{
    $.post("/saida/excluir", {id: id}, function(result)
    {
        if(result == "ok")
            document.location.href = "/saida";
        else
            alert(result);
    });
}

function mostrarSaida(idSaida)
{
    mostrarNovaSaida();
    $("#criarCancelar").html("Voltar");
    var formNovaSaida = document.querySelector("#formNovaSaida");
    desabilitaEdicao(formNovaSaida);
    var btm = $("#btAlterar");
    btm.show();
    btm = $("#btExcluir");
    btm.show();
    
    var btAlterar = formNovaSaida.querySelector("#btAlterar");
    btAlterar.innerHTML="Alterar";
    btAlterar.onclick = function(event){
        if(btAlterar.innerHTML=="Alterar"){
            btAlterar.innerHTML="Cancelar";
            abilitaEdicao(formNovaSaida);
            formNovaSaida.setAttribute("action", "/saida/alterar?id="+idSaida);
        }else{
            desabilitaEdicao(formNovaSaida);
            btAlterar.innerHTML="Alterar";
            formNovaSaida.setAttribute("action", "/saida/salvar");
        }
    }
    
    var btExcluir = document.querySelector("#btExcluir");
    btExcluir.onclick = function(event){
        removerSaida(idSaida);
    }
    
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
            var selectMat = document.querySelector("#materiaisTodos");
            var inputMat2 = linha.querySelector("input[name=lote]");
            inputMat2.setAttribute("lote-id", mat.lote_id);
            var opt = selectMat.querySelector("option[lote-id='"+mat.lote_id+"']");
            if(mat.lote_id==0)
                opt = selectMat.querySelector("option[material-id='"+mat.material_id+"']");
            var materialNome = opt.getAttribute("value");
            materialNome = materialNome.substring(0, materialNome.lastIndexOf('qtd:') );
            inputMat2.value = materialNome;
            linha.querySelector("input[name=quantidade]").value = mat.quantidade;
            linha.querySelector("input[name=material]").value = mat.material_id;
            
            maisUmMaterial();
        }
        document.querySelector("#tabelaMateriais tbody tr:last-child").remove();
        desabilitaEdicao(formNovaSaida);
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
    btm = $("#btAlterar");
    btm.hide();
    btm = $("#btExcluir");
    btm.hide();
}

function validarSalvarSaida()
{    
    var isAlterar = $("#formNovaSaida").prop("action").indexOf("/saida/alterar")>-1;
    var inputs = $("#tabelaMateriais :input");    
    
    for(var i=0; i<inputs.length; i++)
    {
        var input = inputs[i];
        var name = input.getAttribute("name");
        if (name=="lote")
        {
            idLote = parseInt( input.getAttribute("lote-id") );
            input.remove();
        }
        else{
            input.setAttribute("name", name+"_"+idLote);
        }
    }
    
    return true;
}