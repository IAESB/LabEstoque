#include "lote.h"


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

Lote::Lote(sql::ResultSet &rs)
{
    id = rs.getInt(1);
    nome = rs.getString(2);
    validade = rs.getString(3);
	quantidade = rs.getInt(4);
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

