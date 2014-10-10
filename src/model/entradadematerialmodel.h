#ifndef ENTRADADEMATERIALMODEL_H
#define ENTRADADEMATERIALMODEL_H

#include "dao/dao.h"
#include "entity/entradadematerial.h"

class EntradaDeMaterialModel
{
    DaoPrt dao;
public:
    EntradaDeMaterialModel();
    EntradaDeMaterialList getListEntradaDeMaterial();
};

#endif // ENTRADADEMATERIALMODEL_H
