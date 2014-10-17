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

Laboratorio::Laboratorio(int id)
{
    this->id = id;
}

Laboratorio::Laboratorio(sql::ResultSet &rs)
{
    id = rs.getInt(1);
    nome = rs.getString(2);
}

string Laboratorio::getSqlInsert()
{
    return "INSERT INTO laboratorio (nome) VALUE('"+nome+"')";
}
