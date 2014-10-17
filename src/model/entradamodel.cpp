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

void EntradaModel::salvaEntrada(Entrada &entrada)
{
     entrada.setId(dao->insert(entrada));
}

void EntradaModel::salvaListEntradaDeMaterial(EntradaDeMaterialList& list)
{
    if(list->size())
        salvaEntrada(*list->at(0)->getEntrada());

    for(EntradaDeMaterialPtr entradaDeMaterial: *list)
    {
        MateiralPtr mat = entradaDeMaterial->getMaterial();
        mat->setQuantidade(entradaDeMaterial->getQuantidade());
        materialModel.incrementaQuantidadeMaterial(mat);
        dao->insert(*entradaDeMaterial);
    }
}
