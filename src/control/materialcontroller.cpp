#include "materialcontroller.h"
#include "view/view.h"


MaterialController::MaterialController()
{
}

void MaterialController::listaMateriais(Request &request, StreamResponse &response)
{
    calassomys::View view;
    view.setContent(ifstream("WebContent/template.html"));
    view.insertContentId("conteudo", ifstream("WebContent/materiais.html"));
    try{
        GrupoList grupoList = model.getListGrupo();
        for(GrupoPtr& grupo: *grupoList)
        {
            view.insertContentId("grupos", "<option value='"+grupo->getNome()+"'>");
        }
        MateiralList list = model.getListMaterial();
        for(MateiralPtr& material: *list)
        {
            const string& img = material->getImagem().size()?material->getImagem():"/images/ampolas.jpg";
            string html = "<div class='material' >\
                    <img alt='' src='"+img+"'/>\
                    <h4>"+material->getNome()+"</h4>\
                    <label>"+material->getDescricao()+"</label>\
                    <label>"+material->getGrupo()->getNome()+"</label>\
                    <label>quantidade: "+to_string(material->getQuantidade())+"</label>\
                    </div>";
                    view.insertContentId("listMateiral", html);
        }
        response << view;
    }
    catch(exception &ex){
        string erro = "Não foi possível listar os produtos. Por favor tente mais tarde!<br>";
        mensagem(response, erro+ex.what());
    }
}

void MaterialController::salvarMaterial(Request &request, StreamResponse &response)
{
    const string& nome = request.get("nome");
    const string& descricao = request.get("descricao");
    const string& grupo = request.get("grupo");
    const string& imagem = request.get("imagem");
    const string& quantidade = request.get("quantidade");

    Mateiral material;
    material.setNome(nome);
    material.setDescricao(descricao);
    if(!grupo.empty())
        material.setGrupo(GrupoPtr(new Grupo(grupo)));
    material.setImagem(imagem);
    material.setQuantidade(stoi(quantidade));

    try{
        model.salvarMaterial(material);
        response.setCode(301);
        response.setHeader("Location", "/");
    }catch(const exception& ex){
        string msg = "<h1>Erro ao salvar o material</h1><br>";
        msg += ex.what();        
        this->mensagem(response, msg);
    }
}

void MaterialController::setup()
{
    addRoute("GET", "/", MaterialController, listaMateriais);
    addRoute("POST", "/material/salvar", MaterialController, salvarMaterial);
}
