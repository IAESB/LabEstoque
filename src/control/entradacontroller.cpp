#include "entradacontroller.h"
#include "view/view.h"
#include "entity/entradadematerial.h"

EntradaController::EntradaController()
{
}

void EntradaController::setup()
{
    addRoute("GET", "/entrada", EntradaController, listaEntrada);
    addRoute("POST", "/entrada/salvar", EntradaController, salvaEntrada);
}

void EntradaController::listaEntrada(Request &request, StreamResponse &response)
{
    calassomys::View view;
    view.setContent(ifstream("WebContent/template.html"));
    view.insertContentId("conteudo", ifstream("WebContent/entrada.html"));
    MateiralList materialList;
    EntradaList entradaList;
    try{
        materialList = model.getListMaterial();
        for(MateiralPtr& material: *materialList)
        {
            view.insertContentId("materiais", "<option label='"+material->getNome()+"'>"+to_string(material->getId())+"</option>");
        }

        entradaList = model.getListEntrada();
        for(EntradaPtr& entrada: *entradaList)
        {
            string html = "<tr>\
                    <td>"+entrada->getData().substr(0,10)+"</td>\
                    <td>"+entrada->getFornecedor()+"</td>\
                    <td>"+entrada->getAnotacao()+"</td>\
                </tr>";
            view.insertContentId("tabelaEntrada", html);
        }
        response << view;
    }
    catch(exception& ex){
        string erro = "Não foi possível listar os produtos. Por favor tente mais tarde!<br>";
        mensagem(response, erro+ex.what());
        return;
    }
}

void EntradaController::salvaEntrada(Request &request, StreamResponse &response)
{
    map<string, string> variables = request.getAllVariable();    
    EntradaPtr entrada(new Entrada());
    entrada->setData(variables["data"]);
    entrada->setFornecedor(variables["fornecedor"]);
    variables.erase("data");
    variables.erase("fornecedor");

    MateiralPtr mat;
    EntradaDeMaterialPtr entradaDeMaterial;
    EntradaDeMaterialList vecEntradaMaetrial(new vector<EntradaDeMaterialPtr>);
    int idMat=0;
    int i=0;
    for(const pair<string,string>& par: variables)
    {
        switch (i) {
        case 0:
            entradaDeMaterial = EntradaDeMaterialPtr(new EntradaDeMaterial);
            entradaDeMaterial->setQuantidade(stoi(par.second));
            idMat = stoi(par.first.substr(par.first.find('_')+1));
            mat.reset( new Mateiral(idMat) );
            entradaDeMaterial->setMaterial(mat);
            entradaDeMaterial->setEntrada(entrada);
            vecEntradaMaetrial->push_back(entradaDeMaterial);
            break;
        case 1:
            entradaDeMaterial->setValidade(par.second);
            break;
        case 2:
            entradaDeMaterial->setValor(stof(par.second));
            break;
        }
        i++;
    }
    try{
        model.salvaListEntradaDeMaterial(vecEntradaMaetrial);
    }
    catch(exception& ex){
        string msg = "<h1 class='erro'>Não foi possivel salvar as entradas</h1>";
        mensagem(response, msg+ex.what());
        return;
    }

    listaEntrada(request, response);
}
