var Material = function()
{
	this.nome="";
	this.descricao="";
	this.lote="";
	this.validade="";
	this.imagem="";
}

function mostrarFormNovoMaterial()
{
	$(".formNovoMaterial").toggle();
}
function getTodosMateriais()
{
	var list = new Array;	
	var mat = new Material();
	mat.nome = "Acido";
	mat.lote="9s8fjv";
	list.push(mat);
	mat = new Material();
	mat.nome="açucar";
	mat.validade="01/05/2013";
	list.push(mat);
	return list;
}
function mostrarTodosMateriais()
{
	var listMateriais = getTodosMateriais();
	alert(listMateriais);	
}
