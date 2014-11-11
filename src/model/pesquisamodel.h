#ifndef RELATORIOMODEL_H
#define RELATORIOMODEL_H

#include "model.h"
#include "materialmodel.h"
#include "entradadematerialmodel.h"
#include "saidadematerialmodel.h"
#include "entity/pesquisa.h"

class PesquisaModel : public Model
{
    MaterialModel materialModel;
    EntradaDeMaterialModel entradaDeMaterialModel;
    SaidaDeMaterialModel saidaDeMaterialModel;
public:
    PesquisaModel();
    MateiralList getListMaterial();
    EntradaDeMaterialList getListEntradaDeMaterial(Pesquisa& pesquisa);
    SaidaDeMaterialList getListSaidaDeMaterial(Pesquisa& pesquisa);
};

#endif // RELATORIOMODEL_H
