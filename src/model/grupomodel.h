#ifndef GRUPOMODEL_H
#define GRUPOMODEL_H

#include "entity/grupo.h"
#include "dao/dao.h"

class GrupoModel
{
    DaoPrt dao;
public:
    GrupoModel();
    int salvarGrupo(Grupo& grupo);
    GrupoList getListGrupo(string where="");
};

#endif // GRUPOMODEL_H
