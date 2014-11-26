#include "laboratoriomodel.h"

LaboratorioModel::LaboratorioModel()
{
    dao = Dao::getInstance();
}

LaboratorioList LaboratorioModel::getlistLaboratorio()
{
    return dao->select<Laboratorio>("laboratorio");
}

void LaboratorioModel::salvarLaboratorio(Laboratorio &laboratorio)
{
    LaboratorioList list = dao->select<Laboratorio>("laboratorio", "*", "WHERE nome='"+laboratorio.getNome()+"'");// COLLATE utf8_general_ci");
    if(list->size() && list->at(0)->getNome() == laboratorio.getNome()){
        laboratorio.setId(list->at(0)->getId());
    }
    else{
        laboratorio.setId(dao->insert(laboratorio));
    }
}
