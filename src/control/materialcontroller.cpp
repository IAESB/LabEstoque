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
            const string& img = material->getImagem().size()?material->getImagem():"/images/tyre.png";
            string html = "<div class='material' >\
                    <img alt='' src='"+img+"'/>\
                    <h4>"+material->getNome()+"</h4>\
                    <label>"+material->getDescricao()+"</label>\
                    <label>"+material->getGrupo()->getNome()+"</label>\
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
    const string& lote = request.get("lote");
    const string& validade = request.get("validade");
    const string& grupo = request.get("grupo");
    const string& imagem = request.get("imagem");

    Mateiral material;
    material.setNome(nome);
    material.setDescricao(descricao);
    if(!grupo.empty())
        material.setGrupo(GrupoPtr(new Grupo(grupo)));
    material.setImagem(imagem);

    string msg = "<h1>Erro ao salvar o material</h1><br>";
    try{
        if(model.salvarMaterial(material)>0)
            msg = "<h1>Sucesso ao salvar o material!!!</h1>";
    }catch(const exception& ex){
        msg += ex.what();
    }catch(...){
    }
    this->mensagem(response, msg);
}

void MaterialController::setup()
{
    addRoute("GET", "/", MaterialController, listaMateriais);
    addRoute("POST", "/material/salvar", MaterialController, salvarMaterial);
}
