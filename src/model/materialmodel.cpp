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

MateiralPtr MaterialModel::getMaterialPorId(const int& id)
{
    MateiralList list = dao->select<Mateiral>("material", "*", "WHERE id="+to_string(id));
    MateiralPtr mat;
    if(list->size()>0)
        mat = list->at(0);
    return mat;
}

int MaterialModel::salvarMaterial(Mateiral &material)
{
    if(material.getGrupo())
        grupoModel.salvarGrupo( *(material.getGrupo()) );
    return dao->insert(material);
}

MateiralList MaterialModel::getListMaterial()
{
    MateiralList listMat = dao->select<Mateiral>("material m", "m.id, m.nome, m.descricao, m.imagem, g.id, g.nome", "LEFT outer JOIN grupo g ON(m.grupo_id=g.id)");
    return listMat;
}

GrupoList MaterialModel::getListGrupo()
{
    return grupoModel.getListGrupo();
}
