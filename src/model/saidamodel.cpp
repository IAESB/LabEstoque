#include "saidamodel.h"

SaidaModel::SaidaModel()
{
}

SaidaPtr SaidaModel::getSaidaPorId(string id)
{
    auto list = dao->select<Saida>("saida", "*", "WHERE id="+id);
    if(list->size()>0){
        SaidaPtr saida = list->at(0);
        SaidaDeMaterialList list = saidaDeMaterialModel.getListSaidaDeMaterial(saida);
        saida->setSaidaDeMateriais(list);
        return saida;
    }
    return SaidaPtr();
}

MateiralList SaidaModel::getListMaterial()
{
    return materialModel.getListMaterial();
}

LaboratorioList SaidaModel::getListLaboratorio()
{
    return laboratorioModel.getlistLaboratorio();
}

SolicitanteList SaidaModel::getListSolicitantes()
{
    return solicitanteModel.getListSolicitantes();
}

SaidaList SaidaModel::getListSaidas()
{
    return dao->select<Saida>("saida s", "s.*, l.nome as lab", "LEFT OUTER JOIN laboratorio l ON(s.laboratorio_id=l.id) ORDER BY s.id DESC");
}

void SaidaModel::salvaSaida(SaidaPtr& saida)
{
    solicitanteModel.salvaSolicitante(*saida->getSolicitante());
    laboratorioModel.salvarLaboratorio(*saida->getLaboratorio());
    saida->setId( dao->insert(*saida) );
    saidaDeMaterialModel.salvaSaidaDeMaterial( saida->getSaidaDeMaterialList() );
}


