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
        matJ["material"] = mat->getMaterial()->getId();
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
		response << "0k";
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
    view.setContent(ifstream("WebContent/template.html"));
    view.insertContentId("conteudo", ifstream("WebContent/saida.html"));
    MateiralList materialList = model.getListMaterial();
    for(MateiralPtr& material: *materialList)
        view.insertContentId("materiais", "<option value='"+to_string(material->getId())+"'>"+material->getNome()+"</option>");
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
	map<string, string> variables = request.getAllVariable();
	SolicitantePtr solicitante(new Solicitante);
	solicitante->setNome(variables["solicitante"]);
	LaboratorioPtr laboratorio(new Laboratorio);
	laboratorio->setNome(variables["laboratorio"]);
	string data = variables["data"];
	variables.erase("solicitante");
	variables.erase("data");
	variables.erase("laboratorio");
	SaidaPtr saida(new Saida);
	saida->setData(data);
	saida->setSolicitante(solicitante);
	saida->setLaboratorio(laboratorio);

	SaidaDeMaterialList vecMateriais(new vector<SaidaDeMaterialPtr>);
	while (variables.size())
	{
		auto itr = variables.begin();
		string id = itr->first;
		id = id.substr(id.find('_') + 1);
		MateiralPtr material(new Mateiral(stoi(id)));

		SaidaDeMaterialPtr saidaDeMaterial(new SaidaDeMaterial);
		saidaDeMaterial->setMaterial(material);
		saidaDeMaterial->setSaida(saida);
		saidaDeMaterial->setQuantidade(stoi(variables["quantidade_" + id]));
		variables.erase("quantidade_" + id);

		vecMateriais->push_back(saidaDeMaterial);
	}
	saida->setSaidaDeMateriais(vecMateriais);

	return saida;
}