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

SaidaDeMaterialList SaidaDeMaterialModel::getListSaidaDeMaterial(SaidaPtr &saida)
{
    return dao->select<SaidaDeMaterial>("saida_de_material", "*", "WHERE saida_id="+to_string(saida->getId()));
}
