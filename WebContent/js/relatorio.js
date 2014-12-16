
$(function()
{
    $("input[name=entrada]").prop( "checked", true );
    $("input[name=saida]").prop( "checked", true );
    $("input[name=materialChk]").prop( "checked", true );
    
    var params = urlParameters();
    var inputs = document.querySelectorAll("#formNovoRelatorio input");
    if( params.length>0)
    for(var i=0; i<inputs.length; i++)
    {        
        if(inputs[i].name == "entrada") {
            if(params[inputs[i].name]!="on"){
                inputs[i].checked = false;
                $("#relatorioEntrada").hide();
            }        
        }else if(inputs[i].name == "saida"){
            if(params[inputs[i].name]!="on"){
                inputs[i].checked = false; 
                $("#relatorioSaida").hide();
            } 
        }else if(inputs[i].name == "materialChk"){
            if(params[inputs[i].name]!="on"){
                inputs[i].checked = false;
                $("#relatorioMaterial").hide();
            } 
        }
        else{
            inputs[i].value = params[inputs[i].name];
        }
    }
    verificaNecessdidadePeriodo();
    
    var materiais = window.location.search.split("material=");
    for(var i=0; i<materiais.length; i++)
    {      
        if(i==0)continue;
        var value = materiais[i].substring(0, materiais[i].indexOf('&'));
        var opt = document.querySelector("#formNovoRelatorio select option[value='"+value+"'");
        opt.selected=true;
    } 
    
    
    // zera o relatorio se não preencheu os campos de pesquisa
    if($("#dataInicial").html()=="----")
        $("#relatorio").html("");
});

function imiprimirRelatorio()
{
    $("#relatorio").printElement();
}

function mostrarDetalheMaterial(check)
{
    if(check.checked){
        $("#relatorioMaterial").show();
    }
    else{
        $("#relatorioMaterial").hide();
    }
    verificaNecessdidadePeriodo();
}

function mostrarDetalheEntrada(check)
{
    if(check.checked){
        $("#detalheEntrada").show();
        $("#relatorioEntrada").show();
    }
    else{
        $("#detalheEntrada").hide();
        $("#relatorioEntrada").hide();
    }
    verificaNecessdidadePeriodo();
}

function mostrarDetalheSaida(check)
{
    if(check.checked){
        $("#detalheSaida").show();
        $("#relatorioSaida").show();
    }
    else{
        $("#detalheSaida").hide();
        $("#relatorioSaida").hide();
    }
    verificaNecessdidadePeriodo();
}

function verificaNecessdidadePeriodo()
{
    if($("input[name=entrada]").prop( "checked") || $("input[name=saida]").prop( "checked") )
    {
        $("input[name=dataIncial]").attr("required", "");
        $("input[name=dataFinal]").attr("required", "");
    }
    else
    {
        $("input[name=dataIncial]").removeAttr("required");
        $("input[name=dataFinal]").removeAttr("required");
    }
}

