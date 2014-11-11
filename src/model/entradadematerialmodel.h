#ifndef ENTRADADEMATERIALMODEL_H
#define ENTRADADEMATERIALMODEL_H

#include "dao/dao.h"
#include "entity/entradadematerial.h"
#include "entity/pesquisa.h"

class EntradaDeMaterialModel
{
    DaoPrt dao;
public:
    EntradaDeMaterialModel();
    EntradaDeMaterialList getListEntradaDeMaterial(string id="");
    EntradaDeMaterialList getListEntradaDeMaterial(Pesquisa& relatorio);
};

#endif // ENTRADADEMATERIALMODEL_H
