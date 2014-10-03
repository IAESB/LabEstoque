#include "materialmodel.h"

MaterialModel::MaterialModel()
{
    dao = Dao::getInstance();
}

bool MaterialModel::alterarMaterial(Mateiral &material)
{
    return dao->update(material);
}

bool MaterialModel::excluirMaterial(Mateiral &material)
{
    return dao->remove(material);
}

int MaterialModel::salvarMaterial(Mateiral &material)
{
    grupoModel.salvarGrupo( *(material.getGrupo()) );
    return dao->insert(material);
}

ListMateiral MaterialModel::getListMaterial()
{
    ListMateiral listMat = dao->select<Mateiral>("material m, grupo g", "m.id, m.nome, m.formula, m.lote, m.validade, g.id, g.nome", "m.grupo_id = g.id");
    return listMat;
}
