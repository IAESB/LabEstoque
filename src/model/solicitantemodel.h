#ifndef SOLICITANTEMODEL_H
#define SOLICITANTEMODEL_H

#include "entity/solicitante.h"
#include "model.h"

class SolicitanteModel : public Model
{
public:
    SolicitanteModel();
    void salvaSolicitante(Solicitante& solicitante);
    SolicitanteList getListSolicitantes();
};

#endif // SOLICITANTEMODEL_H
