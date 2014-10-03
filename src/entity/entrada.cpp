#include "entrada.h"


int Entrada::getId() const
{
    return id;
}

void Entrada::setId(int value)
{
    id = value;
}

string Entrada::getData() const
{
    return data;
}

void Entrada::setData(const string &value)
{
    data = value;
}

int Entrada::getQuantidade() const
{
    return quantidade;
}

void Entrada::setQuantidade(int value)
{
    quantidade = value;
}

UsuarioPtr Entrada::getUsuario() const
{
    return usuario;
}

void Entrada::setUsuario(const UsuarioPtr &value)
{
    usuario = value;
}

MateiralPtr Entrada::getMaterial() const
{
    return material;
}

void Entrada::setMaterial(const MateiralPtr &value)
{
    material = value;
}
Entrada::Entrada()
{
}
