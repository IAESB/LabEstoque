#include "lote.h"
#include "util.hpp"

int Lote::getId() const
{
    return id;
}

void Lote::setId(int value)
{
    id = value;
}

string Lote::getNome() const
{
    return nome;
}

void Lote::setNome(const string &value)
{
    nome = value;
}

string Lote::getValidade() const
{
    return validade;
}

void Lote::setValidade(const string &value)
{
    validade = value;
}

int Lote::getQuantidade() const
{
    return quantidade;
}

void Lote::setQuantidade(int value)
{
    quantidade = value;
}
Lote::Lote()
{
    id = 0;
}

Lote::Lote(const int &id)
{
    this->id = id;
}

Lote::Lote(soci::row &rs)
{
    id = rs.get<int>(0);
    nome = rs.get<string>(1);
    validade = to_string( rs.get<tm>(2) );
    quantidade = rs.get<int>(3);
}

string Lote::getSqlInsert()
{
    return "INSERT INTO lote(nome, validade, quantidade) VALUES('"+nome+"', '"+validade+"', '"+to_string(quantidade)+"')";
}

string Lote::getSqlUpdate()
{
    return "UPDATE lote SET nome='"+nome+"', validade='"+validade+"', quantidade='"+to_string(quantidade)+"' WHERE id="+to_string(id);
}

string Lote::getSqlDelete()
{
    return "DELETE FROM lote WHERE id="+to_string(id);
}

