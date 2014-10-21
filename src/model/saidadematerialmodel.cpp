#include "saidadematerialmodel.h"

SaidaDeMaterialModel::SaidaDeMaterialModel()
{
}

void SaidaDeMaterialModel::salvaSaidaDeMaterial(SaidaDeMaterial &saidaDeMaterial)
{
    dao->insert(saidaDeMaterial);
}


void SaidaDeMaterialModel::salvaSaidaDeMaterial(const SaidaDeMaterialList &saidaDeMaterialList)
{
    for(SaidaDeMaterialPtr saida: *saidaDeMaterialList)
        salvaSaidaDeMaterial(*saida);
}

void SaidaDeMaterialModel::alterarSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList)
{
	throw __FUNCTION__" esta bugada!";
	for (SaidaDeMaterialPtr saida : *saidaDeMaterialList)
		dao->update(*saida);
}

void SaidaDeMaterialModel::removerSaidaDeMaterial(const Saida& saida)
{
	dao->executeSql("DELETE FROM saida_de_material WHERE saida_id=" + to_string(saida.getId()));
}

SaidaDeMaterialList SaidaDeMaterialModel::getListSaidaDeMaterial(SaidaPtr &saida)
{
    return dao->select<SaidaDeMaterial>("saida_de_material", "*", "WHERE saida_id="+to_string(saida->getId()));
}
