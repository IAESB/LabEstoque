#ifndef SAIDADEMATERIALMODEL_H
#define SAIDADEMATERIALMODEL_H

#include "entity/saidadematerial.h"
#include "entity/pesquisa.h"
#include "model.h"
#include "materialmodel.h"

class SaidaDeMaterialModel : public Model
{
	MaterialModel materialModel;
public:
    SaidaDeMaterialModel();
	void salvaSaidaDeMaterial(SaidaDeMaterial& saidaDeMaterial);
	void salvaSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void alterarSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void removerSaidaDeMaterial(SaidaPtr& saida);
    SaidaDeMaterialList getListSaidaDeMaterial(SaidaPtr& saida);
    SaidaDeMaterialList getListSaidaDeMaterial(Pesquisa& pesquisa);
};

#endif // SAIDADEMATERIALMODEL_H
