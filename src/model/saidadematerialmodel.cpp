#include "saidadematerialmodel.h"
#include "util.hpp"

SaidaDeMaterialModel::SaidaDeMaterialModel()
{
}

void SaidaDeMaterialModel::salvaSaidaDeMaterial(SaidaDeMaterial &saidaDeMaterial)
{
    dao->insert(saidaDeMaterial);
	materialModel.decrementaQuantidadeMaterial(saidaDeMaterial.getMaterial());
    loteModel.decrementaLote(*saidaDeMaterial.getLote());
}


void SaidaDeMaterialModel::salvaSaidaDeMaterial(const SaidaDeMaterialList &saidaDeMaterialList)
{
    for(SaidaDeMaterialPtr saida: *saidaDeMaterialList)
        salvaSaidaDeMaterial(*saida);
}

void SaidaDeMaterialModel::alterarSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList)
{
    throw __FUNCTION__; //" esta bugada!";
	for (SaidaDeMaterialPtr saida : *saidaDeMaterialList)
		dao->update(*saida);
}

void SaidaDeMaterialModel::removerSaidaDeMaterial(SaidaPtr& saida)
{
	SaidaDeMaterialList list = getListSaidaDeMaterial(saida);
    for (SaidaDeMaterialPtr& sm : *list){
		materialModel.incrementaQuantidadeMaterial(sm->getMaterial());
        loteModel.incrementaLote(*sm->getLote());
    }

    dao->executeUpdate("DELETE FROM saida_de_material WHERE saida_id=" + to_string(saida->getId()));
}

SaidaDeMaterialList SaidaDeMaterialModel::getListSaidaDeMaterial(SaidaPtr &saida)
{
    return dao->select<SaidaDeMaterial>("saida_de_material", "*", "WHERE saida_id="+to_string(saida->getId()));
}

SaidaDeMaterialList SaidaDeMaterialModel::getListSaidaDeMaterial(Pesquisa &pesquisa)
{
	string condicoes;
	condicoes += pesquisa.getQuantidadeSaidaDe() > -1 ? " AND sm.quantidade >=" + to_string(pesquisa.getQuantidadeSaidaDe()) : "";
	condicoes += pesquisa.getQuantidadeSaidaAte() > -1 ? " AND sm.quantidade <=" + to_string(pesquisa.getQuantidadeSaidaAte()) : "";
	condicoes += pesquisa.getSolicitante().size() ? " AND so.nome LIKE '%"+pesquisa.getSolicitante()+"%'" : "";
    condicoes += pesquisa.getLaboratorio().size() ? " AND l.nome LIKE '%"+pesquisa.getLaboratorio()+"%'" : "";
    condicoes += pesquisa.getLote().size() ? " AND lo.nome LIKE '%"+pesquisa.getLote()+"%'" : "";

	string materiais;
	for (string& id : pesquisa.getMateriais())
		materiais += (materiais.empty() ? " m.id=" : " OR m.id=") + id;

    ResultSet linhas = dao->executeQuery("SELECT * FROM material m \
                                  LEFT OUTER JOIN grupo g ON(m.grupo_id=g.id) \
                                  LEFT OUTER JOIN saida_de_material sm ON(sm.material_id=m.id) \
                                  LEFT OUTER JOIN saida s ON(sm.saida_id = s.id) \
                                  LEFT OUTER JOIN laboratorio l ON( s.laboratorio_id=l.id) \
                                  LEFT OUTER JOIN solicitante so ON(s.solicitante_id=so.id) \
                                  LEFT OUTER JOIN lote lo ON(lo.id = sm.lote_id) \
                                  WHERE s.data>='" + pesquisa.getData_inicial() + "' AND s.data<='" + pesquisa.getData_fianal() + "'"
								  + (materiais.empty() ? "" : " AND (" + materiais + ")")
                                  +condicoes);

    SaidaDeMaterialList list( new vector<SaidaDeMaterialPtr>() );
    for(soci::row& rs: linhas)
    {
        MateiralPtr material(new Mateiral());
        material->setNome(rs.get<string>(1));
        material->setDescricao(rs.get<string>(2));
        material->setImagem(rs.get<string>(3));
        material->setQuantidade(rs.get<int>(4));

        GrupoPtr grupo(new Grupo());
        grupo->setId(rs.get<int>(6, 0));
        grupo->setNome(rs.get<string>(7, ""));
        material->setGrupo(grupo);

        SaidaDeMaterialPtr saidaDeMaterial(new SaidaDeMaterial());
        saidaDeMaterial->setMaterial(material);
        saidaDeMaterial->setQuantidade(rs.get<int>(13));

        SaidaPtr saida(new Saida());
        saida->setData(to_string( rs.get<tm>(15) ));

		LaboratorioPtr laboratorio(new Laboratorio);
        laboratorio->setNome(rs.get<string>(21));

		SolicitantePtr solicitante(new Solicitante());
        solicitante->setNome(rs.get<string>(23));

        LotePtr lote(new Lote);
        lote->setId(rs.get<int>(25, 0));
        lote->setNome(rs.get<string>(26, ""));

		saida->setLaboratorio(laboratorio);
		saida->setSolicitante(solicitante);
		saidaDeMaterial->setSaida(saida);
        saidaDeMaterial->setLote(lote);
		list->push_back(saidaDeMaterial);
    }

    return list;
}

bool SaidaDeMaterialModel::existeSaidaApartirDasEntradas(EntradaDeMaterialList entMatList)
{
    string lotesId;
    string matsId;
    for(EntradaDeMaterialPtr& entMat: *entMatList){
        if(lotesId.empty()){
            lotesId= "lote_id=" + to_string(entMat->getLote()->getId());
            matsId = "material_id=" + to_string(entMat->getMaterial()->getId());
        }else{
            lotesId+=" OR lote_id="+to_string(entMat->getLote()->getId());
            matsId = " OR material_id=" + to_string(entMat->getMaterial()->getId());
        }
    }
    auto result = dao->select<SaidaDeMaterial>("saida_de_material", "*", "WHERE ("+matsId+(lotesId.empty()?"":") AND ("+lotesId)+")");

    return result->size();
}
