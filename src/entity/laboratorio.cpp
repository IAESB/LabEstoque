#include "laboratorio.h"


int Laboratorio::getId() const
{
    return id;
}

void Laboratorio::setId(int value)
{
    id = value;
}

string Laboratorio::getNome() const
{
    return nome;
}

void Laboratorio::setNome(const string &value)
{
    nome = value;
}
Laboratorio::Laboratorio()
{
}
