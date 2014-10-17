#ifndef SAIDAMODEL_H
#define SAIDAMODEL_H

#include "materialmodel.h"
#include "laboratoriomodel.h"
#include "solicitantemodel.h"
#include "saidadematerialmodel.h"

class SaidaModel : public Model
{
    MaterialModel materialModel;
    LaboratorioModel laboratorioModel;
    SolicitanteModel solicitanteModel;
    SaidaDeMaterialModel saidaDeMaterialModel;
public:
    SaidaModel();
    SaidaPtr getSaidaPorId(string id);
    MateiralList getListMaterial();
    LaboratorioList getListLaboratorio();
    SolicitanteList getListSolicitantes();
    SaidaList getListSaidas();
    void salvaSaida(SaidaPtr& saida);
};

#endif // SAIDAMODEL_H
