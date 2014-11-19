#include "entradadematerialmodel.h"

EntradaDeMaterialModel::EntradaDeMaterialModel()
{
    dao = Dao::getInstance();
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial(string idEntrada)
{
    return dao->select<EntradaDeMaterial>("entrada_de_material em ",
                                          "em.*, e.*, m.*, l.*",
                                          "LEFT OUTER JOIN entrada e ON(em.entrada_id=e.id) \
                                           LEFT OUTER JOIN material m ON(em.material_id=m.id) \
                                           LEFT OUTER JOIN lote l ON(em.lote_id=l.id) \
                                           WHERE em.entrada_id="+idEntrada);
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial(Pesquisa& pesquisa)
{
    string matDe = (pesquisa.getQuantidadeMaterialDe()<0)?"":" AND m.quantidade>="+to_string(pesquisa.getQuantidadeMaterialDe());
    string matAte = (pesquisa.getQuantidadeMaterialAte()<0) ? "" : " AND m.quantidade<=" + to_string(pesquisa.getQuantidadeMaterialAte());
	string entrada;
    entrada += pesquisa.getLote().empty() ? "" : " AND l.nome LIKE '%" + pesquisa.getLote() + "%'";
    entrada += pesquisa.getValidadade().empty() ? "" : " AND l.validade LIKE '%" + pesquisa.getValidadade() + "%'";
    entrada += pesquisa.getValor()<0 ? "" : " AND em.valor LIKE '%" + to_string(pesquisa.getValor()) + "%'";
    entrada += pesquisa.getFornecedor().empty() ? "" : " AND e.fornecedor LIKE '%" + pesquisa.getFornecedor() + "%'";
    entrada += pesquisa.getQuantidadeEntradaDe()<0 ? "" : " AND em.quantidade>=" + to_string( pesquisa.getQuantidadeEntradaDe() );
    entrada += pesquisa.getQuantidadeEntradaAte()<0 ? "" : " AND em.quantidade<=" + to_string( pesquisa.getQuantidadeEntradaAte() );

	string materiais;
    for (string& id : pesquisa.getMateriais())
		materiais += (materiais.empty()?" m.id=":" OR m.id=") + id;

    ResultSet rs = dao->executeQuery("SELECT * FROM material m \
							   LEFT OUTER JOIN grupo g ON(m.grupo_id=g.id)\
                               LEFT OUTER JOIN entrada_de_material em ON(em.material_id=m.id) \
                               LEFT OUTER JOIN entrada e ON(em.entrada_id=e.id) \
                               LEFT OUTER JOIN lote l ON(em.lote_id=l.id) \
                               WHERE e.data>='" + pesquisa.getData_inicial() + "' AND e.data<='" + pesquisa.getData_fianal() + "'"
							   +(materiais.empty()?"":" AND ("+materiais+")")
							   +matDe
							   +matAte
							   +entrada);

	
	EntradaDeMaterialList list(new vector<EntradaDeMaterialPtr>);
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
		EntradaDeMaterialPtr entradaMaterial(new EntradaDeMaterial());
        entradaMaterial->setValor(rs->getDouble(14));
		entradaMaterial->setQuantidade(rs->getInt(15));
        EntradaPtr entrada(new Entrada());
        entrada->setData(rs->getString(17));
        entrada->setFornecedor(rs->getString(18));
        entrada->setAnotacao(rs->getString(19));
        LotePtr lote(new Lote);
        lote->setId(rs->getInt(21));
        lote->setNome(rs->getString(22));
        lote->setValidade(rs->getString(23));
        entradaMaterial->setLote(lote);
        entradaMaterial->setEntrada(entrada);
        entradaMaterial->setMaterial(material);

        list->push_back(entradaMaterial);
	}
    return list;
}

EntradaDeMaterialList EntradaDeMaterialModel::getListMaterialComLote()
{
    const auto& rs = dao->executeQuery("SELECT DISTINCT m.*, l.* FROM lote l \
                                        RIGHT OUTER JOIN entrada_de_material em ON(em.lote_id = l.id) \
                                        RIGHT OUTER JOIN  material m ON(m.id = em.material_id) \
                                        ORDER BY m.nome");

	EntradaDeMaterialList list(new vector<EntradaDeMaterialPtr>);
	while (rs->next())
	{
		MateiralPtr material(new Mateiral());
		material->setId(rs->getInt(1));
		material->setNome(rs->getString(2));
		material->setDescricao(rs->getString(3));
		material->setImagem(rs->getString(4));
		material->setQuantidade(rs->getInt(5));

		LotePtr lote(new Lote);
		lote->setId(rs->getInt(7));
		lote->setNome(rs->getString(8));
		lote->setValidade(rs->getString(9));
		lote->setQuantidade(rs->getInt(10));

		EntradaDeMaterialPtr entradaMaterial(new EntradaDeMaterial());
        entradaMaterial->setMaterial(material);
		entradaMaterial->setLote(lote);
		list->push_back(entradaMaterial);
	}
	return list;
}

void EntradaDeMaterialModel::salvarEntradaDeMaterial(EntradaDeMaterial &entradaDeMaterial)
{
    MateiralPtr mat = entradaDeMaterial.getMaterial();
    mat->setQuantidade(entradaDeMaterial.getQuantidade());
    materialModel.incrementaQuantidadeMaterial(mat);
    LotePtr lote = entradaDeMaterial.getLote();
    lote->setQuantidade(entradaDeMaterial.getQuantidade());
    loteModel.salvarLote(*lote);
    dao->insert(entradaDeMaterial);
}
