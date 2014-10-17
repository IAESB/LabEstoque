#ifndef LABORATORIOMODEL_H
#define LABORATORIOMODEL_H

#include "entity/laboratorio.h"
#include "dao/dao.h"

class LaboratorioModel
{
    DaoPrt dao;
public:
    LaboratorioModel();
    LaboratorioList getlistLaboratorio();
    void salvarLaboratorio(Laboratorio& laboratorio);
};

#endif // LABORATORIOMODEL_H
