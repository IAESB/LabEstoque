#include "materialmodel.h"

MaterialModel::MaterialModel()
{
    dao = Dao::getInstance();
}

bool MaterialModel::alterarMaterial(Mateiral &material)
{
	if (material.getGrupo())
		grupoModel.salvarGrupo(*(material.getGrupo()));
    return dao->update(material);
}

bool MaterialModel::excluirMaterial(Mateiral &material)
{
    return dao->remove(material);
}

bool MaterialModel::incrementaQuantidadeMaterial(MateiralPtr material)
{
	MateiralPtr matBase = getMaterialPorId(material->getId());
	if (!matBase){
		salvarMaterial(*material);
		return true;
	}
	else{
		matBase->setQuantidade(material->getQuantidade() + matBase->getQuantidade());
		return dao->update(*matBase);
	}
}
bool MaterialModel::decrementaQuantidadeMaterial(MateiralPtr material)
{
	MateiralPtr matBase = getMaterialPorId(material->getId());
	if (matBase){
		matBase->setQuantidade(matBase->getQuantidade() - material->getQuantidade());
		return dao->update(*matBase);
	}
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
    material.setId( dao->insert(material) );
    return material.getId();
}

MateiralList MaterialModel::getListMaterial()
{
    MateiralList listMat = dao->select<Mateiral>("material m", "m.id, m.nome, m.descricao, m.imagem, m.quantidade, g.id as grupo_id, g.nome as grupo_nome", "LEFT OUTER JOIN grupo g ON(m.grupo_id=g.id) ORDER BY m.nome");
    return listMat;
}

GrupoList MaterialModel::getListGrupo()
{
    return grupoModel.getListGrupo();
}
