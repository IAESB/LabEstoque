
$(function()
{
    $("input[name=entrada]").prop( "checked", true );
    $("input[name=saida]").prop( "checked", true );
    
    var params = urlParameters();
    var inputs = document.querySelectorAll("#formNovoRelatorio input");
    if( params.length>0)
    for(var i=0; i<inputs.length; i++)
    {
        if(inputs[i].name == "saida"){
            if(params[inputs[i].name]!="on"){
                inputs[i].checked = false; } 
        }
        else if(inputs[i].name == "entrada") {
            if(params[inputs[i].name]!="on"){
                inputs[i].checked = false;}
        }
        else{
            inputs[i].value = params[inputs[i].name];
        }
    }
    
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

function mostrarDetalheSaida(check)
{
    if(check.checked)
        $("#detalheSaida").show();
    else
        $("#detalheSaida").hide();
}

function mostrarDetalheEntrada(check)
{
    if(check.checked)
        $("#detalheEntrada").show();
    else
        $("#detalheEntrada").hide();
}

