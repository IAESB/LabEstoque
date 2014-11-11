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
	addRoute("POST", "/entrada/alterar", EntradaController, alterarEntrada);
	addRoute("POST", "/entrada/excluir", EntradaController, excluirEntrada);
}

void EntradaController::listaEntrada(Request &request, StreamResponse &response)
{
    calassomys::View view;
	view.setContent(ifstream(server->getOption("document_root") + "/template.html"));
	view.insertContentId("conteudo", ifstream(server->getOption("document_root") + "/entrada.html"));
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

EntradaDeMaterialList EntradaController::criarEntradas(Request& request)
{
	multimap<string, string> variables = request.getAllVariable();
	EntradaPtr entrada(new Entrada());
	entrada->setData(variables.find("data")->second);
	entrada->setFornecedor(variables.find("fornecedor")->second);
	entrada->setAnotacao(variables.find("anotacao")->second);
	variables.erase("data");
	variables.erase("fornecedor");
	variables.erase("anotacao");
	variables.erase("id");

	MateiralPtr material;
	EntradaDeMaterialPtr entradaDeMaterial;
	EntradaDeMaterialList vecEntradaMaetrial(new vector<EntradaDeMaterialPtr>);
	while (variables.size())
	{
		auto itr = variables.begin();
		string id = itr->first;
		id = id.substr(id.find('_') + 1);
		material = MateiralPtr(new Mateiral(stoi(id.find("novo") ? id : "0")));
		material->setNome(variables.find("material_" + id)->second);
		variables.erase("material_" + id);

		entradaDeMaterial = EntradaDeMaterialPtr(new EntradaDeMaterial);
		entradaDeMaterial->setMaterial(material);
		entradaDeMaterial->setEntrada(entrada);
		vecEntradaMaetrial->push_back(entradaDeMaterial);

		itr = variables.find("quantidade_" + id);
		if (itr != variables.end())
		{
			entradaDeMaterial->setQuantidade(stoi(itr->second));
			variables.erase(itr);
		}
		itr = variables.find("validade_" + id);
		if (itr != variables.end())
		{
			entradaDeMaterial->setValidade(itr->second);
			variables.erase(itr);
		}
		itr = variables.find("lote_" + id);
		if (itr != variables.end())
		{
			entradaDeMaterial->setLote(itr->second);
			variables.erase(itr);
		}
		itr = variables.find("valor_" + id);
		if (itr != variables.end())
		{
			entradaDeMaterial->setValor(stof(itr->second.empty() ? "0" : itr->second));
			variables.erase(itr);
		}
	}

	return vecEntradaMaetrial;
}

void EntradaController::alterarEntrada(Request &request, StreamResponse &response)
{
	try{
		model.alterarListEntradaDeMaterial(criarEntradas(request), request.get("id"));
		redirecionar(response, "/entrada");
	}
	catch (exception& ex){
		string msg = "<h1 class='erro'>Não foi possivel alterar as entradas</h1>";
		mensagem(response, msg + ex.what());
		return;
	}
}

void EntradaController::excluirEntrada(Request &request, StreamResponse &response)
{
	try{
		model.excluirEntrada( request.get("id") );
		response << "ok";
	}
	catch (exception& ex){
		string msg = "Não foi possivel Excluir a entrada\n";
		cerr << msg << ex.what() << endl;
		response << msg << ex.what();
		return;
	}
}

void EntradaController::salvaEntrada(Request &request, StreamResponse &response)
{
    try{        
        model.salvaListEntradaDeMaterial(criarEntradas(request));
		redirecionar(response, "/entrada");
    }
    catch(exception& ex){
        string msg = "<h1 class='erro'>Não foi possivel salvar as entradas</h1>";
        mensagem(response, msg+ex.what());
        return;
    }
}

void EntradaController::getEntrada(Request &request, StreamResponse &response)
{
    Json::Value json;
    string idEntrada = request.get("id");
    EntradaDeMaterialList list = model.getListEntradaDeMaterial(idEntrada);
    if(list->size()){
		json["data"] = list->at(0)->getEntrada()->getData();
		json["fornecedor"] = list->at(0)->getEntrada()->getFornecedor();
		json["anotacao"] = list->at(0)->getEntrada()->getAnotacao();
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
