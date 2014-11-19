#include "lotemodel.h"

LoteModel::LoteModel()
{
}

void LoteModel::salvarLote(Lote &lote)
{
    if(lote.getNome().empty())
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

void LoteModel::decrementaLote(Lote &lote)
{
    LoteList loteBase = dao->select<Lote>("lote", "*", "WHERE id='" + to_string(lote.getId()) + "'");
    if (loteBase->size()){
        loteBase->at(0)->setQuantidade( loteBase->at(0)->getQuantidade() - lote.getQuantidade() );
        dao->update(*loteBase->at(0));
        lote.setQuantidade(loteBase->at(0)->getQuantidade());
    }
}

void LoteModel::incrementaLote(Lote &lote)
{
    LoteList loteBase = dao->select<Lote>("lote", "*", "WHERE id='" + to_string(lote.getId()) + "'");
    if (loteBase->size()){
        loteBase->at(0)->setQuantidade( loteBase->at(0)->getQuantidade() + lote.getQuantidade() );
        dao->update(*loteBase->at(0));
    }
}

void LoteModel::removeLote(Lote &lote)
{
    dao->executeUpdate("DELETE FROM lote WHERE id="+to_string(lote.getId()) );
}
