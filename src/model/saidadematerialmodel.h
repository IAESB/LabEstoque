#ifndef SAIDADEMATERIALMODEL_H
#define SAIDADEMATERIALMODEL_H

#include "entity/saidadematerial.h"
#include "model.h"

class SaidaDeMaterialModel : public Model
{
public:
    SaidaDeMaterialModel();
	void salvaSaidaDeMaterial(SaidaDeMaterial& saidaDeMaterial);
	void salvaSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void alterarSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void removerSaidaDeMaterial(const Saida& saida);
    SaidaDeMaterialList getListSaidaDeMaterial(SaidaPtr& saida);
};

#endif // SAIDADEMATERIALMODEL_H
