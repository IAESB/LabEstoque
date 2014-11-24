#include "entradamodel.h"

EntradaModel::EntradaModel()
{
    dao = Dao::getInstance();
}

MateiralList EntradaModel::getListMaterial()
{
    return materialModel.getListMaterial();
}

EntradaList EntradaModel::getListEntrada()
{
    return dao->select<Entrada>("entrada", "*", "ORDER BY id DESC");
}

EntradaDeMaterialList EntradaModel::getListEntradaDeMaterial(const string& idEntrada)
{
    return entradaDeMaterialModel.getListEntradaDeMaterial(idEntrada);
}

MateiralPtr EntradaModel::getMaterialPorId(const int &id)
{
    return materialModel.getMaterialPorId(id);
}

void EntradaModel::alterarEntrada(Entrada& entrada)
{
	if (!dao->update(entrada))
		throw runtime_error("Não foi possível alterar a entrada");
}

void EntradaModel::salvaEntrada(Entrada &entrada)
{
     entrada.setId(dao->insert(entrada));
}

void EntradaModel::alterarListEntradaDeMaterial(const EntradaDeMaterialList& list, const string id)
{
	EntradaPtr ent;
	if (list->size()){
		ent = list->at(0)->getEntrada();
		ent->setId(stoi(id));
		alterarEntrada(*ent);
	}
	EntradaDeMaterialList listDecrement = entradaDeMaterialModel.getListEntradaDeMaterial(id);
	for (EntradaDeMaterialPtr entradaDeMaterial : *listDecrement)
	{
		MateiralPtr mat = entradaDeMaterial->getMaterial();
		mat->setQuantidade(entradaDeMaterial->getQuantidade());
		materialModel.decrementaQuantidadeMaterial(mat);
	}

    dao->executeUpdate("DELETE FROM entrada_de_material WHERE entrada_id=" + id);
    for (EntradaDeMaterialPtr entradaDeMaterial : *list)
    {
        entradaDeMaterialModel.salvarEntradaDeMaterial(*entradaDeMaterial);
    }
}

void EntradaModel::salvaListEntradaDeMaterial(const EntradaDeMaterialList& list)
{
    if(list->size())
        salvaEntrada(*list->at(0)->getEntrada());

    for(EntradaDeMaterialPtr entradaDeMaterial: *list)
    {
        entradaDeMaterialModel.salvarEntradaDeMaterial(*entradaDeMaterial);
    }
}

void EntradaModel::excluirEntrada(string id)
{
    EntradaDeMaterialList emList = entradaDeMaterialModel.getListEntradaDeMaterial(id);
    if(saidaDeMaterialModel.existeSaidaApartirDasEntradas(emList))
        throw std::runtime_error("Inpossível remover entradas que ja existem saida");

    dao->executeUpdate("DELETE FROM entrada_de_material WHERE entrada_id=" + id);

    for(EntradaDeMaterialPtr& em: *emList){
        MateiralPtr material = em->getMaterial();
        material->setQuantidade(em->getQuantidade());
        materialModel.decrementaQuantidadeMaterial(material);
        LotePtr lote = em->getLote();
        lote->setQuantidade(em->getQuantidade());
        loteModel.decrementaLote(*lote);
        if(lote->getQuantidade()<1)
            loteModel.removeLote(*lote);
    }
    dao->executeUpdate("DELETE FROM entrada WHERE id=" + id);
}
