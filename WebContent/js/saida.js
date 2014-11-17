function desabilitaEdicao(formNovaSaida)
{
    var fields =  formNovaSaida.querySelectorAll("input, select");
    for(var i=0; i<fields.length; i++)
        fields[i].setAttribute("disabled", true);
    var buttons = formNovaSaida.querySelectorAll("fieldset button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "none";
    
    var btAlterar = formNovaSaida.querySelector("#btSalvar");
    btAlterar.style.display = "none";
        
}

function abilitaEdicao(formNovaSaida)
{
    var fields =  formNovaSaida.querySelectorAll("input, select");
    for(var i=0; i<fields.length; i++)
        fields[i].removeAttribute("disabled");
    
    var buttons = formNovaSaida.querySelectorAll("button");
    for(var i=0; i<buttons.length; i++)
        buttons[i].style.display = "inline";  
    
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
            var selectMat = linha.querySelector("#materiais");
            var inputMat2 = linha.querySelector("input[name=material]");
            selectMat.value = mat.material_id;
            var materialNome = selectMat.querySelector("option[material-id='"+mat.material_id+"']").getAttribute("value");
            materialNome = materialNome.substring(0, materialNome.lastIndexOf('-') );
            inputMat2.value = materialNome;
            linha.querySelector("input[name=quantidade]").value = mat.quantidade;
            
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
	var idMaterial =-1;
    var erro = false;
    var isAlterar = $("#formNovaSaida").prop("action").indexOf("/saida/alterar")>-1;
    var inputs = $("#tabelaMateriais :input");
    var qtd;
    for(var i=0; i<inputs.length; i++)
    {
        var input = inputs[i];
        var name = input.getAttribute("name");
        if (name=="material")
        {            
            var opt = document.querySelector("#tabelaMateriais option[value='"+input.value+"']");
            qtd = parseInt( opt.attributes.qtd.value );
        }
        else if(name=="quantidade")
        {
            var valorInput = parseInt(input.value);            
            qtd += isAlterar?valorInput:0;
            if( qtd < valorInput ){
                input.style.borderColor="red";
                erro = true;
            }
        }
    }
    if(erro){
        return false;
    }
    
    for(var i=0; i<inputs.length; i++)
    {
        var input = inputs[i];
        var name = input.getAttribute("name");
        if (name=="material")
        {      
            var opt = document.querySelector("#tabelaMateriais option[value='"+input.value+"']");
            idMaterial = parseInt( opt.getAttribute("material-id") );
            input.remove();
        }
        else{
            input.setAttribute("name", name+"_"+idMaterial);
        }
    }
    
    return true;
}