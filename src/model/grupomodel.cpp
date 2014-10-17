#include "grupomodel.h"

GrupoModel::GrupoModel()
{
    dao = Dao::getInstance();
}

int GrupoModel::salvarGrupo(Grupo &grupo)
{
    if(grupo.getGrupo())
        this->salvarGrupo(*(grupo.getGrupo()) );
    auto id=-1;
    GrupoList list = getListGrupo("nome='"+grupo.getNome()+"'");
    if(list->empty())
    {
        id = dao->insert(grupo);
        grupo.setId(id);
    }
    else
    {
        grupo.setId((*list)[0]->getId());
        id = grupo.getId();
    }
    return id;
}

GrupoList GrupoModel::getListGrupo(string where)
{
    where = where.empty()?"":"WHERE "+where;
    GrupoList list = dao->select<Grupo>("grupo","*", where);
    return list;
}
