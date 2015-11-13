#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "grupomodel.h"
#include "entity/mateiral.h"
#include "entity/pesquisa.h"
#include "entity/entradadematerial.h"
#include "dao/dao.h"


class MaterialModel
{
    DaoPrt dao;
    GrupoModel grupoModel;
public:
    MaterialModel();
    int salvarMaterial(Mateiral& material);
    bool alterarMaterial(Mateiral& material);
	bool excluirMaterial(Mateiral& material);
	bool incrementaQuantidadeMaterial(MateiralPtr material);
	bool decrementaQuantidadeMaterial(MateiralPtr material);
    MateiralPtr getMaterialPorId(const int& id);
    MateiralList getListMaterial();
    EntradaDeMaterialList getListMaterialComLote();
    MateiralList getListMaterial(Pesquisa& pesquisa);
    GrupoList getListGrupo();
};

#endif // MATERIALMODEL_H
