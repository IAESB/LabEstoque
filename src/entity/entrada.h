#ifndef ENTRADA_H
#define ENTRADA_H

#include <cppconn/resultset.h>
#include "usuario.h"
#include "mateiral.h"

class Entrada
{
    int id;
    string data;
    string fornecedor;
    string anotacao;
    UsuarioPtr usuario;
public:
    Entrada();
    Entrada(sql::ResultSet& rs);
    string getSqlInsert();
    int getId() const;
    void setId(int value);
    string getData() const;
    void setData(const string &value);
    UsuarioPtr getUsuario() const;
    void setUsuario(const UsuarioPtr &value);
    string getFornecedor() const;
    void setFornecedor(const string &value);
    string getAnotacao() const;
    void setAnotacao(const string &value);
};
typedef shared_ptr<Entrada> EntradaPtr;
typedef shared_ptr< vector<EntradaPtr> > EntradaList;
#endif // ENTRADA_H
