#ifndef ENTRADADEMATERIAL_H
#define ENTRADADEMATERIAL_H

#include <cppconn/resultset.h>
#include "entrada.h"
#include "mateiral.h"
#include "lote.h"

class EntradaDeMaterial
{
    EntradaPtr entrada;
    MateiralPtr material;
    LotePtr lote;
    float valor;
    int quantidade;

public:
    EntradaDeMaterial();
    EntradaDeMaterial(sql::ResultSet& rs);
    string getSqlInsert();
    EntradaPtr getEntrada() const;
    void setEntrada(const EntradaPtr &value);
    MateiralPtr getMaterial() const;
    void setMaterial(const MateiralPtr &value);
    float getValor() const;
    void setValor(float value);
    int getQuantidade() const;
    void setQuantidade(int value);
    LotePtr getLote() const;
    void setLote(const LotePtr &value);
};

typedef shared_ptr<EntradaDeMaterial> EntradaDeMaterialPtr;
typedef shared_ptr< vector<EntradaDeMaterialPtr> > EntradaDeMaterialList;

#endif // ENTRADADEMATERIAL_H
