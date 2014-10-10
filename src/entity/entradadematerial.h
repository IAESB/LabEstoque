#ifndef ENTRADADEMATERIAL_H
#define ENTRADADEMATERIAL_H

#include <cppconn/resultset.h>
#include "entrada.h"
#include "mateiral.h"

class EntradaDeMaterial
{
    EntradaPtr entrada;
    MateiralPtr material;
    string lote;
    float valor;
    string validade;
    int quantidade;

public:
    EntradaDeMaterial();
    EntradaDeMaterial(sql::ResultSet& rs);
    string getSqlInsert();
    EntradaPtr getEntrada() const;
    void setEntrada(const EntradaPtr &value);
    MateiralPtr getMaterial() const;
    void setMaterial(const MateiralPtr &value);
    string getLote() const;
    void setLote(const string &value);
    float getValor() const;
    void setValor(float value);
    string getValidade() const;
    void setValidade(const string &value);
    int getQuantidade() const;
    void setQuantidade(int value);
};

typedef shared_ptr<EntradaDeMaterial> EntradaDeMaterialPtr;
typedef shared_ptr< vector<EntradaDeMaterialPtr> > EntradaDeMaterialList;

#endif // ENTRADADEMATERIAL_H
