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

Solicitante::Solicitante(sql::ResultSet &rs)
{
    id = rs.getInt(1);
    nome = rs.getString(2);
    matricula = rs.getString(3);
}

string Solicitante::getSqlInsert()
{
    return "INSERT INTO solicitante (nome, matricula)\
                  VALUE ('"+nome+"', '"+matricula+"');";
}
