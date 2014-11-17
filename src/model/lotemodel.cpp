#include "lotemodel.h"

LoteModel::LoteModel()
{
}

void LoteModel::salvarLote(Lote &lote)
{
	if (lote.getNome().empty())
		return;

	LoteList loteBase = dao->select<Lote>("lote", "*", "WHERE nome='" + lote.getNome() + "'");
	if (loteBase->size()){
		lote.setQuantidade(lote.getQuantidade() + loteBase->at(0)->getQuantidade());
		lote.setId(loteBase->at(0)->getId());
		dao->update(lote);
	}else{
		lote.setId(dao->insert(lote));
	}
}
