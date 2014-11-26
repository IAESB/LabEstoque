#include "saidacontroller.h"
#include "view/view.h"
#include "jsoncpp/json/json.h"

SaidaController::SaidaController()
{
}

void SaidaController::setup()
{
    addRoute("GET", "/saida", SaidaController, listaSaida);
	addRoute("GET", "/saida/get", SaidaController, getSaida);
	addRoute("POST", "/saida/salvar", SaidaController, salvarSaida);
	addRoute("POST", "/saida/alterar", SaidaController, alterarSaida);
	addRoute("POST", "/saida/excluir", SaidaController, excluirSaida);
}

void SaidaController::getSaida(Request &request, StreamResponse &response)
{
    SaidaPtr saida = model.getSaidaPorId(request.get("id"));
    Json::Value json;
    json["data"] = saida->getData();
    json["laboratorio"] = saida->getLaboratorio()->getId();
    json["solicitante"] = saida->getSolicitante()->getId();
    json["anotacao"] = saida->getAnotacao();
    for(SaidaDeMaterialPtr& mat: *saida->getSaidaDeMaterialList())
    {
        Json::Value matJ;
        matJ["lote_id"] = mat->getLote()->getId();
        matJ["material_id"] = mat->getMaterial()->getId();
        matJ["quantidade"] = mat->getQuantidade();
        json["materiais"].append(matJ);
    }
    response << json;
}

void SaidaController::alterarSaida(Request &request, StreamResponse &response)
{
	try{
		SaidaPtr saida = criarSaida(request);
		saida->setId(stoi(request.get("id")));
		model.alterarSaida(saida);
		response.setCode(301);
		response.setHeader("Location", "/saida");
    }
    catch (const exception& ex){
        cerr << ex.what() << endl;
        cerr << booster::trace(ex);
		mensagem(response, ex.what());
	}
}

void SaidaController::excluirSaida(Request &request, StreamResponse &response)
{
	try{
		model.excluirSaida( request.get("id") );
		response << "ok";
    }
    catch (const exception& ex){
        cerr << ex.what() << endl;
		response << ex.what();
	}
}

void SaidaController::salvarSaida(Request &request, StreamResponse &response)
{
	try{
		SaidaPtr saida = criarSaida(request);
        model.salvaSaida(saida);

        response.setCode(301);
        response.setHeader("Location", "/saida");

    }catch(exception& ex){
        mensagem(response, ex.what());
        cerr << ex.what() << endl;
    }

}

void SaidaController::listaSaida(Request &request, StreamResponse &response)
{
    calassomys::View view;
	view.setContent(ifstream(server->getOption("document_root") + "/template.html"));
	view.insertContentId("conteudo", ifstream(server->getOption("document_root") + "/saida.html"));
    
    string option;
	EntradaDeMaterialList materialList = model.getListMaterial();
    int qtd;
	for (EntradaDeMaterialPtr& ent : *materialList){
		MateiralPtr material = ent->getMaterial();
		LotePtr lote = ent->getLote();
        qtd = lote->getQuantidade()?lote->getQuantidade():material->getQuantidade();
        option = "<option material-id='" + to_string(material->getId())
                + "' qtd='" + to_string(qtd)
                + "' lote-id='"+ to_string(lote->getId())
                + "' value='" + material->getNome() + ", lot:"+lote->getNome()+", val:"+lote->getValidade()+", qtd:" + to_string(qtd) + "'>"
                + "</option>";
        if(lote->getQuantidade()>0 || material->getQuantidade()>0)
            view.insertContentId("materiais", option);
        view.insertContentId("materiaisTodos", option);
	}
    
	LaboratorioList laboratorioList = model.getListLaboratorio();
    for(LaboratorioPtr& laboratorio: *laboratorioList)
        view.insertContentId("laboratorios",
             "<option value='"+laboratorio->getNome()+"' label='"+to_string(laboratorio->getId())+"'></option>");
    
	SolicitanteList solicitantes = model.getListSolicitantes();
    for(SolicitantePtr& solicitante: *solicitantes)
        view.insertContentId("solicitantes", "<option value='"+solicitante->getNome()+"' label='"+to_string(solicitante->getId())+"'></option>");
    
	SaidaList saidas = model.getListSaidas();
    for(SaidaPtr& saida: *saidas)
    {
        string html = "<tr onclick='mostrarSaida("+to_string(saida->getId())+");'>\
                <td>"+saida->getData().substr(0,10)+"</td>\
                <td>"+saida->getLaboratorio()->getNome()+"</td>\
				<td>" + saida->getSolicitante()->getNome() + "</td>\
            </tr>";
        view.insertContentId("tabelaSaida", html);
    }
    response << view;
}

SaidaPtr SaidaController::criarSaida(Request& request)
{
    auto variables = request.getAllVariable();
	SolicitantePtr solicitante(new Solicitante);
	solicitante->setNome(variables.find("solicitante")->second);
	LaboratorioPtr laboratorio(new Laboratorio);
	laboratorio->setNome(variables.find("laboratorio")->second);
	string data = variables.find("data")->second;
    string anotacao = variables.find("anotacao")->second;
	variables.erase("solicitante");
    variables.erase("data");
    variables.erase("laboratorio");
    variables.erase("anotacao");
    auto itr = variables.find("id");
    if (itr != variables.end())
        variables.erase(itr);

	SaidaPtr saida(new Saida);
	saida->setData(data);
	saida->setSolicitante(solicitante);
	saida->setLaboratorio(laboratorio);
    saida->setAnotacao(anotacao);

	SaidaDeMaterialList vecMateriais(new vector<SaidaDeMaterialPtr>);
	while (variables.size())
	{
        itr = variables.begin();
		string id = itr->first;
		size_t fTraco = id.find('_');
		id = id.substr(fTraco + 1);

        itr = variables.find("quantidade_" + id);
        int qtd = stoi(itr->second);
        variables.erase(itr);

        itr = variables.find("material_" + id);
        MateiralPtr material(new Mateiral( stoi(itr->second) ));
		material->setQuantidade(qtd);
        variables.erase(itr);

		SaidaDeMaterialPtr saidaDeMaterial(new SaidaDeMaterial);
		saidaDeMaterial->setMaterial(material);
		saidaDeMaterial->setSaida(saida);
		saidaDeMaterial->setQuantidade(qtd);

        LotePtr lote(new Lote);
        lote->setId(stoi(id));
        lote->setQuantidade(qtd);
        saidaDeMaterial->setLote(lote);

		vecMateriais->push_back(saidaDeMaterial);
	}
	saida->setSaidaDeMateriais(vecMateriais);

	return saida;
}
