#include "solicitantemodel.h"

SolicitanteModel::SolicitanteModel()
{
}

void SolicitanteModel::salvaSolicitante(Solicitante &solicitante)
{
    SolicitanteList tem = dao->select<Solicitante>("solicitante", "*", "WHERE nome='"+solicitante.getNome()+"'");
    if(tem->size()){
        solicitante.setId(tem->at(0)->getId());
        solicitante.setNome(tem->at(0)->getNome());
    }
    else{
        solicitante.setId(dao->insert(solicitante));
    }
}

SolicitanteList SolicitanteModel::getListSolicitantes()
{
    return dao->select<Solicitante>("solicitante");
}
