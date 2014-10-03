#include "solicitante.h"


int Solicitante::getId() const
{
    return id;
}

void Solicitante::setId(int value)
{
    id = value;
}

string Solicitante::getNome() const
{
    return nome;
}

void Solicitante::setNome(const string &value)
{
    nome = value;
}

string Solicitante::getMatricula() const
{
    return matricula;
}

void Solicitante::setMatricula(const string &value)
{
    matricula = value;
}
Solicitante::Solicitante()
{
}
