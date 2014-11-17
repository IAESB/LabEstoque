#include "saidacontroller.h"
#include "view/view.h"
#include "json/json.h"

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
    for(SaidaDeMaterialPtr& mat: *saida->getSaidaDeMaterialList())
    {
		Json::Value matJ;
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
	catch (sql::SQLException& ex){
		mensagem(response, ex.what());
		cerr << ex.what() << endl;
		cerr << ex.getErrorCode() << ex.getSQLState() << endl;
	}
	catch (exception& ex){
		mensagem(response, ex.what());
	}
}

void SaidaController::excluirSaida(Request &request, StreamResponse &response)
{
	try{
		model.excluirSaida( request.get("id") );
		response << "ok";
	}
	catch (sql::SQLException& ex){
		response << ex.what();
		cerr << ex.what() << endl;
		cerr << ex.getErrorCode() << ex.getSQLState() << endl;
	}
	catch (exception& ex){
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
    }catch(sql::SQLException& ex){
        mensagem(response, ex.what());
        cerr << ex.what() << endl;
        cerr << ex.getErrorCode() << ex.getSQLState() << endl;
    }catch(exception& ex){
        mensagem(response, ex.what());
    }

}

void SaidaController::listaSaida(Request &request, StreamResponse &response)
{
    calassomys::View view;
	view.setContent(ifstream(server->getOption("document_root") + "/template.html"));
	view.insertContentId("conteudo", ifstream(server->getOption("document_root") + "/saida.html"));
    
	EntradaDeMaterialList materialList = model.getListMaterial();
	for (EntradaDeMaterialPtr& ent : *materialList){
		MateiralPtr material = ent->getMaterial();
		LotePtr lote = ent->getLote();
		view.insertContentId("materiais", "<option material-id='" + to_string(material->getId()) + "' qtd='" + to_string(lote->getQuantidade()) + "' value='" + material->getNome() + ", "+lote->getNome()+", "+lote->getValidade()+" - " + to_string(lote->getQuantidade()) + "'>" + "</option>");
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
	auto& variables = request.getAllVariable();
	SolicitantePtr solicitante(new Solicitante);
	solicitante->setNome(variables.find("solicitante")->second);
	LaboratorioPtr laboratorio(new Laboratorio);
	laboratorio->setNome(variables.find("laboratorio")->second);
	string data = variables.find("data")->second;
	variables.erase("solicitante");
	variables.erase("data");
	variables.erase("laboratorio");
	auto id = variables.find("id");
	if (id != variables.end())
		variables.erase(id);

	SaidaPtr saida(new Saida);
	saida->setData(data);
	saida->setSolicitante(solicitante);
	saida->setLaboratorio(laboratorio);

	SaidaDeMaterialList vecMateriais(new vector<SaidaDeMaterialPtr>);
	while (variables.size())
	{
		auto itr = variables.begin();
		string id = itr->first;
		size_t fTraco = id.find('_');
		id = id.substr(fTraco + 1);

		int qtd = stoi(variables.find("quantidade_" + id)->second);
		MateiralPtr material(new Mateiral(stoi(id)));
		material->setQuantidade(qtd);

		SaidaDeMaterialPtr saidaDeMaterial(new SaidaDeMaterial);
		saidaDeMaterial->setMaterial(material);
		saidaDeMaterial->setSaida(saida);
		saidaDeMaterial->setQuantidade(qtd);
		variables.erase("quantidade_" + id);

		vecMateriais->push_back(saidaDeMaterial);
	}
	saida->setSaidaDeMateriais(vecMateriais);

	return saida;
}