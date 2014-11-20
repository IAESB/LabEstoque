#ifndef SAIDADEMATERIAL_H
#define SAIDADEMATERIAL_H

#include "saida.h"
#include "mateiral.h"
#include "lote.h"

class Saida;
typedef shared_ptr<Saida> SaidaPtr;
typedef shared_ptr< vector<SaidaPtr> > SaidaList;

class SaidaDeMaterial
{
    SaidaPtr saida;
    MateiralPtr material;
    LotePtr lote;
    int quantidade;
public:
    SaidaDeMaterial();
	SaidaDeMaterial(soci::row& rs);
	string getSqlInsert();
	string getSqlUpdate();
    SaidaPtr getSaida() const;
    void setSaida(const SaidaPtr &value);
    MateiralPtr getMaterial() const;
    void setMaterial(const MateiralPtr &value);
    int getQuantidade() const;
    void setQuantidade(int value);
    LotePtr getLote() const;
    void setLote(const LotePtr &value);
};
typedef shared_ptr<SaidaDeMaterial> SaidaDeMaterialPtr;
typedef shared_ptr< vector<SaidaDeMaterialPtr> > SaidaDeMaterialList;

#endif // SAIDADEMATERIAL_H
