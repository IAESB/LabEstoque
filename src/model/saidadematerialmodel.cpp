#include "saidadematerialmodel.h"

SaidaDeMaterialModel::SaidaDeMaterialModel()
{
}

void SaidaDeMaterialModel::salvaSaidaDeMaterial(SaidaDeMaterial &saidaDeMaterial)
{
    dao->insert(saidaDeMaterial);
	materialModel.decrementaQuantidadeMaterial(saidaDeMaterial.getMaterial());
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
	for (SaidaDeMaterialPtr& sm : *list)
		materialModel.incrementaQuantidadeMaterial(sm->getMaterial());

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

	string materiais;
	for (string& id : pesquisa.getMateriais())
		materiais += (materiais.empty() ? " m.id=" : " OR m.id=") + id;

    auto& rs = dao->executeQuery("SELECT * FROM material m \
                                  LEFT OUTER JOIN grupo g ON(m.grupo_id=g.id) \
                                  LEFT OUTER JOIN saida_de_material sm ON(sm.material_id=m.id) \
                                  LEFT OUTER JOIN saida s ON(sm.saida_id = s.id) \
                                  LEFT OUTER JOIN laboratorio l ON( s.laboratorio_id=l.id) \
                                  LEFT OUTER JOIN solicitante so ON(s.solicitante_id=so.id) \
                                  WHERE s.data>='" + pesquisa.getData_inicial() + "' AND s.data<='" + pesquisa.getData_fianal() + "'"
								  + (materiais.empty() ? "" : " AND (" + materiais + ")")
                                  +condicoes);

    SaidaDeMaterialList list( new vector<SaidaDeMaterialPtr>() );
    while(rs->next())
    {
        MateiralPtr material(new Mateiral());
        material->setNome(rs->getString(2));
        material->setDescricao(rs->getString(3));
        material->setImagem(rs->getString(4));
        material->setQuantidade(rs->getInt(5));

        GrupoPtr grupo(new Grupo());
        grupo->setId(rs->getInt(7));
        grupo->setNome(rs->getString(8));
        material->setGrupo(grupo);

        SaidaDeMaterialPtr saidaDeMaterial(new SaidaDeMaterial());
        saidaDeMaterial->setMaterial(material);
        saidaDeMaterial->setQuantidade(rs->getInt(12 ));

        SaidaPtr saida(new Saida());
        saida->setData(rs->getString(14));

		LaboratorioPtr laboratorio(new Laboratorio);
		laboratorio->setNome(rs->getString(19));

		SolicitantePtr solicitante(new Solicitante());
		solicitante->setNome(rs->getString(21));

		saida->setLaboratorio(laboratorio);
		saida->setSolicitante(solicitante);
		saidaDeMaterial->setSaida(saida);
		list->push_back(saidaDeMaterial);
    }

    return list;
}
