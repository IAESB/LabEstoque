#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "grupomodel.h"
#include "entity/mateiral.h"
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
    MateiralPtr getMaterialPorId(const int& id);
    MateiralList getListMaterial();
    GrupoList getListGrupo();
};

#endif // MATERIALMODEL_H
