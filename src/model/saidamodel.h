#ifndef SAIDAMODEL_H
#define SAIDAMODEL_H

#include "materialmodel.h"
#include "laboratoriomodel.h"
#include "solicitantemodel.h"
#include "saidadematerialmodel.h"
#include "entradadematerialmodel.h"

class SaidaModel : public Model
{
    MaterialModel materialModel;
    LaboratorioModel laboratorioModel;
    SolicitanteModel solicitanteModel;
    SaidaDeMaterialModel saidaDeMaterialModel;
	EntradaDeMaterialModel entradaDeMaterialModel;
public:
    SaidaModel();
    SaidaPtr getSaidaPorId(string id);
    EntradaDeMaterialList getListMaterial();
    LaboratorioList getListLaboratorio();
    SolicitanteList getListSolicitantes();
    SaidaList getListSaidas();
    void salvaSaida(SaidaPtr& saida);
	void alterarSaida(SaidaPtr& saida);
	void excluirSaida(string id);
};

#endif // SAIDAMODEL_H
