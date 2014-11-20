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

    ResultSet linhas = dao->executeQuery("SELECT * FROM material m \
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
    for(soci::row& rs: linhas)
    {
        MateiralPtr material(new Mateiral());
        material->setNome(rs.get<string>(2));
        material->setDescricao(rs.get<string>(3));
        material->setImagem(rs.get<string>(4));
        material->setQuantidade(rs.get<int>(5));
        GrupoPtr grupo(new Grupo());
        grupo->setId(rs.get<int>(7));
        grupo->setNome(rs.get<string>(8));
		material->setGrupo(grupo);
		EntradaDeMaterialPtr entradaMaterial(new EntradaDeMaterial());
        entradaMaterial->setValor(rs.get<double>(14));
        entradaMaterial->setQuantidade(rs.get<int>(15));
        EntradaPtr entrada(new Entrada());
        entrada->setData(rs.get<string>(17));
        entrada->setFornecedor(rs.get<string>(18));
        entrada->setAnotacao(rs.get<string>(19));
        LotePtr lote(new Lote);
        lote->setId(rs.get<int>(21));
        lote->setNome(rs.get<string>(22));
        lote->setValidade(rs.get<string>(23));
        entradaMaterial->setLote(lote);
        entradaMaterial->setEntrada(entrada);
        entradaMaterial->setMaterial(material);

        list->push_back(entradaMaterial);
	}
    return list;
}

EntradaDeMaterialList EntradaDeMaterialModel::getListMaterialComLote()
{
    ResultSet linhas = dao->executeQuery("SELECT DISTINCT m.*, l.* FROM lote l \
                                        RIGHT OUTER JOIN entrada_de_material em ON(em.lote_id = l.id) \
                                        RIGHT OUTER JOIN  material m ON(m.id = em.material_id) \
                                        ORDER BY m.nome");

	EntradaDeMaterialList list(new vector<EntradaDeMaterialPtr>);
    for(soci::row& rs: linhas)
	{
		MateiralPtr material(new Mateiral());
        material->setId(rs.get<int>(0));
        material->setNome(rs.get<string>(1));
        material->setDescricao(rs.get<string>(2));
        material->setImagem(rs.get<string>(3));
        material->setQuantidade(rs.get<int>(4));

		LotePtr lote(new Lote);
        lote->setId(rs.get<int>(6, 0));
        lote->setNome(rs.get<string>(7, ""));
        lote->setValidade(rs.get<string>(8, ""));
        lote->setQuantidade(rs.get<int>(9, 0));

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
