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

Solicitante::Solicitante(int id)
{
    this->id = id;
}

Solicitante::Solicitante(soci::row &rs)
{
    id = rs.get<int>(0);
    nome = rs.get<string>(1);
    matricula = rs.get<string>(2);
}

string Solicitante::getSqlInsert()
{
    return "INSERT INTO solicitante (nome, matricula)\
                  VALUE ('"+nome+"', '"+matricula+"');";
}
