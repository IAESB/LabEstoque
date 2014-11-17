#include "pesquisacontroller.h"
#include "view/view.h"
#include "util.hpp"

PesquisaController::PesquisaController()
{
}

void PesquisaController::setup()
{
    addRoute("GET", "/relatorio", PesquisaController, listaRelatorio);
    addRoute("GET", "/relatorio/pesquisar", PesquisaController, pesquisarRelatorio);
}

void PesquisaController::listaRelatorio(Request &request, StreamResponse& response)
{
    calassomys::View view;
    view.setContent(ifstream(server->getOption("document_root")+"/template.html"));
    view.insertContentId("conteudo", ifstream(server->getOption("document_root") + "/relatorio.html"));
    MateiralList listMat = model.getListMaterial();
    for(MateiralPtr& material: *listMat)
        view.insertContentId("selectMaterial",
		"<option value='"+to_string(material->getId())+"'>"+material->getNome()+"</option>");
    response << view;
}

void PesquisaController::pesquisarRelatorio(Request &request, StreamResponse &response)
{
	try{
		calassomys::View view;
		view.setContent(ifstream(server->getOption("document_root") + "/template.html"));
		view.insertContentId("conteudo", ifstream(server->getOption("document_root") + "/relatorio.html"));

		MateiralList listMat = model.getListMaterial();
		for (MateiralPtr& material : *listMat)
			view.insertContentId("selectMaterial",
			"<option value='" + to_string(material->getId()) + "'>" + material->getNome() + "</option>");

        Pesquisa& pesquisa = criarPesquisa(request);

        view.setContentId("nome", pesquisa.getNome());
        view.setContentId("dataInicial", pesquisa.getData_inicial());
        view.setContentId("dataFinal", pesquisa.getData_fianal());

		string html;
        if (pesquisa.IsEntrada()){
            EntradaDeMaterialList& entradaList = model.getListEntradaDeMaterial(pesquisa);
            for(EntradaDeMaterialPtr& ent: *entradaList){
                html += "<tr>\
                            <td>" + ent->getMaterial()->getNome() + "</td>\
                            <td>" + ent->getEntrada()->getData().substr(0, 10) + "</td>\
                            <td>" + ent->getEntrada()->getFornecedor() + "</td>\
                            <td>" + to_string(ent->getQuantidade()) + "</td>\
                            <td>" + ent->getLote()->getValidade().substr(0, 10) + "</td>\
                            <td>" + ent->getLote()->getNome() + "</td>\
                            <td>" + to_string(ent->getValor(), 2) + "</td>\
                            <td>" + to_string(ent->getMaterial()->getQuantidade()) + "</td>\
                        </tr>\n";
            }
            view.insertContentId("tbodyEntrada", html);
		}
		html.erase();
        if(pesquisa.IsSaida()){
            SaidaDeMaterialList& saidaList = model.getListSaidaDeMaterial(pesquisa);
            for (SaidaDeMaterialPtr& sai : *saidaList)
            {
                html += "<tr> \
                            <td>"+sai->getMaterial()->getNome()+"</td> \
                            <td>"+sai->getSaida()->getData().substr(0,10)+"</td> \
                            <td>"+to_string(sai->getQuantidade())+"</td> \
                            <td>"+sai->getSaida()->getSolicitante()->getNome()+"</td> \
                            <td>"+sai->getSaida()->getLaboratorio()->getNome()+"</td> \
                            <td>" + to_string(sai->getMaterial()->getQuantidade()) + "</td>\
                         </tr>";
            }
            view.insertContentId("tbodySaida", html);
        }
		response << view;
	}
	catch (exception& ex){
		mensagem(response, ex.what());
	}
}

Pesquisa PesquisaController::criarPesquisa(Request &request)
{
    string numero;
    Pesquisa relatorio;
    relatorio.setNome( request.get("nome") );
    relatorio.setDataInicial(request.get("dataIncial"));
    relatorio.setDataFianal( request.get("dataFinal") );
    relatorio.setIsEntrada( request.get("entrada")=="on" );
    relatorio.setIsSaida(request.get("saida")=="on" );
    vector<string> vecIdMaterial;
	auto& vars = request.getAllVariable(); 
	auto& ppp = vars.equal_range("material");
	for (auto it2 = ppp.first; it2 != ppp.second; ++it2){
		vecIdMaterial.push_back(it2->second);
	}
    relatorio.setMateriais(vecIdMaterial);
    numero = request.get("quantidadeMaterialDe");
    relatorio.setQuantidadeMaterialDe(numero.size()?stoi(numero):-1);
    numero = request.get("quantidadeMaterialAte");
    relatorio.setQuantidadeMaterialAte(numero.size() ? stoi(numero) : -1);
	relatorio.setFornecedor(request.get("fornecedor"));
    relatorio.setLote(request.get("lote"));
    relatorio.setValidadade(request.get("validade"));
    numero = request.get("valor");
    relatorio.setValor(numero.size()?stof(numero):-1);
    numero = request.get("quantidadeEntradaDe");
    relatorio.setQuantidadeEntradaDe(numero.size() ? stoi(numero) : -1);
    numero = request.get("quantidadeEntradaAte");
    relatorio.setQuantidadeEntradaAte(numero.size() ? stoi(numero) : -1);
    numero = request.get("quantidadeSaidaDe");
    relatorio.setQuantidadeSaidaDe(numero.size() ? stoi(numero) : -1);
    numero = request.get("quantidadeSaidaAte");
    relatorio.setQuantidadeSaidaAte(numero.size() ? stoi(numero) : -1);
	relatorio.setSolicitante(request.get("solicitante"));
	relatorio.setLaboratorio(request.get("laboratorio"));

    return relatorio;
}
