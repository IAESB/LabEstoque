
function maisUmMaterial()
{
	var novaLinha = $("#linhaMaterial").clone();
	novaLinha.attr("id","");
	novaLinha.find(':input').val('').end();
	$("#tabelaMateriais").append(novaLinha);
	novaLinha.find(':input:first').focus();
	novaLinha.find(':button').prop("disabled",false);
}

function removeMaterial(elemento) {
	var row = elemento.parentNode.parentNode;
	row.remove();
}
