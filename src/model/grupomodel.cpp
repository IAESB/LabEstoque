#include "grupomodel.h"

GrupoModel::GrupoModel()
{
    dao = Dao::getInstance();
}

int GrupoModel::salvarGrupo(Grupo &grupo)
{
    if(grupo.getGrupo())
        this->salvarGrupo(*(grupo.getGrupo()) );

    auto id = dao->insert(grupo);
    grupo.setId(id);
    return id;
}
