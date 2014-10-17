#include "entradacontroller.h"
#include "view/view.h"
#include "entity/entradadematerial.h"
#include <json/json.h>

EntradaController::EntradaController()
{
}

void EntradaController::setup()
{
    addRoute("GET", "/entrada", EntradaController, listaEntrada);
    addRoute("GET", "/entrada/get", EntradaController, getEntrada);
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
            view.insertContentId("materiais",
                                 "<option value='"+material->getNome()+"' label='"+to_string(material->getId())+"'></option>");
        }

        entradaList = model.getListEntrada();
        for(EntradaPtr& entrada: *entradaList)
        {
            string html = "<tr onclick='mostrarEntrada("+to_string(entrada->getId())+");'>\
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
    try{
        map<string, string> variables = request.getAllVariable();
        EntradaPtr entrada(new Entrada());
        entrada->setData(variables["data"]);
        entrada->setFornecedor(variables["fornecedor"]);
        variables.erase("data");
        variables.erase("fornecedor");

        MateiralPtr material;
        EntradaDeMaterialPtr entradaDeMaterial;
        EntradaDeMaterialList vecEntradaMaetrial(new vector<EntradaDeMaterialPtr>);
        while (variables.size())
        {
            auto itr = variables.begin();
            string id = itr->first;
            id = id.substr(id.find('_')+1);
            material = MateiralPtr( new Mateiral(stoi(id.find("novo")?id:"0")) );
            material->setNome(variables["material_"+id]);
            variables.erase("material_"+id);

            entradaDeMaterial = EntradaDeMaterialPtr(new EntradaDeMaterial);
            entradaDeMaterial->setMaterial(material);
            entradaDeMaterial->setEntrada(entrada);
            vecEntradaMaetrial->push_back(entradaDeMaterial);

            itr = variables.find("quantidade_"+id);
            if(itr!=variables.end())
            {
                entradaDeMaterial->setQuantidade(stoi(itr->second));
                variables.erase(itr);
            }
            itr = variables.find("validade_"+id);
            if(itr!=variables.end())
            {
                entradaDeMaterial->setValidade(itr->second);
                variables.erase(itr);
            }
            itr = variables.find("lote_"+id);
            if(itr!=variables.end())
            {
                entradaDeMaterial->setLote(itr->second);
                variables.erase(itr);
            }
            itr = variables.find("valor_"+id);
            if(itr!=variables.end())
            {
				entradaDeMaterial->setValor(stof(itr->second.empty() ? "0" : itr->second));
                variables.erase(itr);
            }
        }
        model.salvaListEntradaDeMaterial(vecEntradaMaetrial);
    }
    catch(exception& ex){
        string msg = "<h1 class='erro'>Não foi possivel salvar as entradas</h1>";
        mensagem(response, msg+ex.what());
        return;
    }

    listaEntrada(request, response);
}

void EntradaController::getEntrada(Request &request, StreamResponse &response)
{
    Json::Value json;
    string idEntrada = request.get("id");
    EntradaDeMaterialList list = model.getListEntradaDeMaterial(idEntrada);
    if(list->size()){
        json["data"] = list->at(0)->getEntrada()->getData();
        json["fornecedor"] = list->at(0)->getEntrada()->getFornecedor();
    }
    for(EntradaDeMaterialPtr ptr: *list) {
        Json::Value mat;
        mat["nome"] = ptr->getMaterial()->getNome();
        mat["quantidade"] = ptr->getQuantidade();
        mat["validade"] = ptr->getValidade();
        mat["valor"] = ptr->getValor();
        mat["lote"] = ptr->getLote();
        json["materiais"].append(mat);
    }
    response << json;
}
