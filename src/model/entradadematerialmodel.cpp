#include "entradadematerialmodel.h"

EntradaDeMaterialModel::EntradaDeMaterialModel()
{
    dao = Dao::getInstance();
}

EntradaDeMaterialList EntradaDeMaterialModel::getListEntradaDeMaterial(string id)
{
    return dao->select<EntradaDeMaterial>("entrada_de_material em ",
                                          "em.*, e.*, m.* ",
                                          "LEFT OUTER JOIN entrada e ON(em.entrada_id=e.id) \
                                           LEFT OUTER JOIN material m ON(em.material_id=m.id) \
                                           WHERE em.entrada_id="+id);
}
