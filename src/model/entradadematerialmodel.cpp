#include "entradadematerialmodel.h"

EntradaDeMaterialModel::EntradaDeMaterialModel()
{
    dao = Dao::getInstance();
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial(string id)
{
    return dao->select<EntradaDeMaterial>("entrada_de_material em ",
                                          "em.*, e.*, m.* ",
                                          "LEFT OUTER JOIN entrada e ON(em.entrada_id=e.id) \
                                           LEFT OUTER JOIN material m ON(em.material_id=m.id) \
                                          WHERE em.entrada_id="+id);
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial(Pesquisa& pesquisa)
{
    string matDe = (pesquisa.getQuantidadeMaterialDe()<0)?"":" AND m.quantidade>="+to_string(pesquisa.getQuantidadeMaterialDe());
    string matAte = (pesquisa.getQuantidadeMaterialAte()<0) ? "" : " AND m.quantidade<=" + to_string(pesquisa.getQuantidadeMaterialAte());
	string entrada;
    entrada += pesquisa.getLote().empty() ? "" : " AND em.lote LIKE '%" + pesquisa.getLote() + "%'";
    entrada += pesquisa.getValidadade().empty() ? "" : " AND em.validade LIKE '%" + pesquisa.getValidadade() + "%'";
    entrada += pesquisa.getValor()<0 ? "" : " AND em.valor LIKE '%" + to_string(pesquisa.getValor()) + "%'";
    entrada += pesquisa.getFornecedor().empty() ? "" : " AND e.fornecedor LIKE '%" + pesquisa.getFornecedor() + "%'";
    entrada += pesquisa.getQuantidadeEntradaDe()<0 ? "" : " AND em.quantidade>=" + to_string( pesquisa.getQuantidadeEntradaDe() );
    entrada += pesquisa.getQuantidadeEntradaAte()<0 ? "" : " AND em.quantidade<=" + to_string( pesquisa.getQuantidadeEntradaAte() );

	string materiais;
    for (string& id : pesquisa.getMateriais())
		materiais += (materiais.empty()?" m.id=":" OR m.id=") + id;
    auto& rs = dao->executeQuery("SELECT * FROM material m \
							   LEFT OUTER JOIN grupo g ON(m.grupo_id=g.id)\
                               LEFT OUTER JOIN entrada_de_material em ON(em.material_id=m.id) \
							   LEFT OUTER JOIN entrada e ON(em.entrada_id=e.id) \
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
		entradaMaterial->setLote(rs->getString(12));
		entradaMaterial->setValor(rs->getDouble(13));
		entradaMaterial->setValidade(rs->getString(14));
		entradaMaterial->setQuantidade(rs->getInt(15));
        EntradaPtr entrada(new Entrada());
        entrada->setData(rs->getString(17));
        entrada->setFornecedor(rs->getString(18));
        entrada->setAnotacao(rs->getString(19));
        entradaMaterial->setEntrada(entrada);
        entradaMaterial->setMaterial(material);

        list->push_back(entradaMaterial);
	}
    return list;
}
