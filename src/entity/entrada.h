#ifndef ENTRADA_H
#define ENTRADA_H

#include "usuario.h"
#include "mateiral.h"

class Entrada
{
    int id;
    string data;
    int quantidade;
    UsuarioPtr usuario;
    MateiralPtr material;
public:
    Entrada();
    int getId() const;
    void setId(int value);
    string getData() const;
    void setData(const string &value);
    int getQuantidade() const;
    void setQuantidade(int value);
    UsuarioPtr getUsuario() const;
    void setUsuario(const UsuarioPtr &value);
    MateiralPtr getMaterial() const;
    void setMaterial(const MateiralPtr &value);
};
typedef shared_ptr<Entrada> EntradaPtr;
#endif // ENTRADA_H
