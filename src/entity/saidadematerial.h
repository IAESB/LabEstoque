#ifndef SAIDADEMATERIAL_H
#define SAIDADEMATERIAL_H

#include "saida.h"
#include "mateiral.h"

class Saida;
typedef shared_ptr<Saida> SaidaPtr;
typedef shared_ptr< vector<SaidaPtr> > SaidaList;

class SaidaDeMaterial
{
    SaidaPtr saida;
    MateiralPtr material;
    int quantidade;
public:
    SaidaDeMaterial();
    SaidaDeMaterial(sql::ResultSet& rs);
    string getSqlInsert();
    SaidaPtr getSaida() const;
    void setSaida(const SaidaPtr &value);
    MateiralPtr getMaterial() const;
    void setMaterial(const MateiralPtr &value);
    int getQuantidade() const;
    void setQuantidade(int value);
};
typedef shared_ptr<SaidaDeMaterial> SaidaDeMaterialPtr;
typedef shared_ptr< vector<SaidaDeMaterialPtr> > SaidaDeMaterialList;

#endif // SAIDADEMATERIAL_H
