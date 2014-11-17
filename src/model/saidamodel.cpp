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

EntradaDeMaterialList SaidaModel::getListMaterial()
{
	return entradaDeMaterialModel.getListMaterialComLote();
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
    return dao->select<Saida>("saida s", "s.*, l.nome as lab, so.nome as solicitante", 
		"LEFT OUTER JOIN laboratorio l ON(s.laboratorio_id = l.id) \
		 LEFT OUTER JOIN solicitante so ON(s.solicitante_id = so.id) \
		 ORDER BY s.id DESC");
}

void SaidaModel::salvaSaida(SaidaPtr& saida)
{
	solicitanteModel.salvaSolicitante(*saida->getSolicitante());
	laboratorioModel.salvarLaboratorio(*saida->getLaboratorio());
	saida->setId(dao->insert(*saida));
	saidaDeMaterialModel.salvaSaidaDeMaterial(saida->getSaidaDeMaterialList());
}

void SaidaModel::alterarSaida(SaidaPtr& saida)
{
	solicitanteModel.salvaSolicitante(*saida->getSolicitante());
	laboratorioModel.salvarLaboratorio(*saida->getLaboratorio());
	dao->update(*saida);
	saidaDeMaterialModel.removerSaidaDeMaterial(saida);
	saidaDeMaterialModel.salvaSaidaDeMaterial(saida->getSaidaDeMaterialList());
}

void SaidaModel::excluirSaida(string id)
{
	SaidaPtr saida = getSaidaPorId(id);
	saidaDeMaterialModel.removerSaidaDeMaterial(saida);
	dao->remove(*saida);
}
