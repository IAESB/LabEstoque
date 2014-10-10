#include "entradadematerialmodel.h"

EntradaDeMaterialModel::EntradaDeMaterialModel()
{
    dao = Dao::getInstance();
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial()
{
    return dao->select<EntradaDeMaterial>("entrada_de_material");
}
