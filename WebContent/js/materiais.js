function mostrarMaterial(id)
{
    var divMaterial = document.querySelector("#mat"+id);
    var formMaterial = document.querySelector(".formNovoMaterial");
    formMaterial.querySelector("input[name=nome]").value = divMaterial.querySelector("h4[name=nome]").innerHTML;
    formMaterial.querySelector("input[name=descricao]").value = divMaterial.querySelector("label[name=descricao]").innerHTML;
    formMaterial.querySelector("input[name=quantidade]").value = divMaterial.querySelector("label[name=quantidade]").innerHTML;
    formMaterial.querySelector("input[name=grupo]").value = divMaterial.querySelector("label[name=grupo]").innerHTML;
    formMaterial.querySelector("input[name=imagem]").value = divMaterial.querySelector("img[name=imagem]").src;
    formMaterial.querySelector("#imgPreview").src = divMaterial.querySelector("img[name=imagem]").src;
    formMaterial.querySelector("input[type=submit]").value="Alterar";
    formMaterial.setAttribute("action", "/material/alterar?id="+id);
    formMaterial.style.display="block";
    var excluir = formMaterial.querySelector("input[value=Excluir]");
    excluir.style.display="";
    excluir.onclick = function(event)
    {
        window.location.href = "/material/excluir?id="+id;
    }; 
}

function mostrarFormNovoMaterial()
{
    var formMaterial = document.querySelector("#formNovoMaterial");
    formMaterial.querySelector("input[type=submit]").value="Salvar";
    formMaterial.setAttribute("action", "/material/salvar");
    var excluir = formMaterial.querySelector("input[value=Excluir]");
    excluir.style.display="none";
	$(".formNovoMaterial").toggle();
}

function encodeImageFileAsURL(){

    var filesSelected = document.getElementById("inputFileToLoad").files;
    if (filesSelected.length > 0)
    {
        var fileToLoad = filesSelected[0];
        var fileReader = new FileReader();
        var type = 'image/png';
        var quality = 0.92;

        fileReader.onload = function(fileLoadedEvent) {
            var srcData = fileLoadedEvent.target.result; // <--- data: base64

            var newImage = document.getElementById('imgPreview');
            newImage.src = srcData;
            var canvas = document.createElement('canvas');
            canvas.height = 120;
            canvas.width = 120;
            var ctx = canvas.getContext('2d');
            ctx.drawImage(newImage, 0, 0, canvas.height, canvas.width);
            newImage.src = canvas.toDataURL(type, quality);
            document.querySelector("#formNovoMaterial input[name=imagem]").value = newImage.src;
            
            console.log("Converted Base64 version is "+newImage.src);
        }
        fileReader.readAsDataURL(fileToLoad);
    }
}
