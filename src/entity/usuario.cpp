#include "usuario.h"


int Usuario::getId() const
{
    return id;
}

void Usuario::setId(int value)
{
    id = value;
}

string Usuario::getNome() const
{
    return nome;
}

void Usuario::setNome(const string &value)
{
    nome = value;
}

string Usuario::getSenha() const
{
    return senha;
}

void Usuario::setSenha(const string &value)
{
    senha = value;
}
Usuario::Usuario()
{
}
