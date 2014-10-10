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
    return dao->select<Entrada>("entrada");
}

EntradaDeMaterialList EntradaModel::getListEntradaDeMaterial()
{
    return entradaDeMaterialModel.getListEntradaDeMaterial();
}

MateiralPtr EntradaModel::getMaterialPorId(const int &id)
{
    return materialModel.getMaterialPorId(id);
}

void EntradaModel::salvaEntrada(Entrada &entrada)
{
    dao->insert(entrada);
}

void EntradaModel::salvaListEntradaDeMaterial(EntradaDeMaterialList& list)
{
    if(list->size())
        salvaEntrada(*list->at(0)->getEntrada());

    for(EntradaDeMaterialPtr entrada: *list)
    {
        dao->insert(*entrada);
    }
}
