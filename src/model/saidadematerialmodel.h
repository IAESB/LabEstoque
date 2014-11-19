#ifndef SAIDADEMATERIALMODEL_H
#define SAIDADEMATERIALMODEL_H

#include "entity/saidadematerial.h"
#include "entity/pesquisa.h"
#include "model.h"
#include "materialmodel.h"
#include "entity/entradadematerial.h"
#include "lotemodel.h"

class SaidaDeMaterialModel : public Model
{
	MaterialModel materialModel;
    LoteModel loteModel;
public:
    SaidaDeMaterialModel();
	void salvaSaidaDeMaterial(SaidaDeMaterial& saidaDeMaterial);
	void salvaSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void alterarSaidaDeMaterial(const SaidaDeMaterialList& saidaDeMaterialList);
	void removerSaidaDeMaterial(SaidaPtr& saida);
    SaidaDeMaterialList getListSaidaDeMaterial(SaidaPtr& saida);
    SaidaDeMaterialList getListSaidaDeMaterial(Pesquisa& pesquisa);
    bool existeSaidaApartirDasEntradas(EntradaDeMaterialList entMatList);
};

#endif // SAIDADEMATERIALMODEL_H
