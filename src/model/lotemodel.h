#ifndef LOTEMODEL_H
#define LOTEMODEL_H

#include "model.h";
#include "entity/lote.h"

class LoteModel : public Model
{
public:
    LoteModel();
	void salvarLote(Lote& lote);
};

#endif // LOTEMODEL_H
