#ifndef ENTRADADEMATERIALMODEL_H
#define ENTRADADEMATERIALMODEL_H

#include "dao/dao.h"
#include "entity/entradadematerial.h"
#include "entity/pesquisa.h"
#include "materialmodel.h"
#include "lotemodel.h"


class EntradaDeMaterialModel
{
    DaoPrt dao;
	MaterialModel materialModel;
	LoteModel loteModel;
public:
    EntradaDeMaterialModel();
	EntradaDeMaterialList getListEntradaDeMaterial(string id = "");
	EntradaDeMaterialList getListEntradaDeMaterial(Pesquisa& relatorio);
    EntradaDeMaterialList getListMaterialComLote(string ordeBy="m.nome");
    void salvarEntradaDeMaterial(EntradaDeMaterial& entradaDeMaterial);
};

#endif // ENTRADADEMATERIALMODEL_H
