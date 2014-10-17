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


UsuarioPtr Entrada::getUsuario() const
{
    return usuario;
}

void Entrada::setUsuario(const UsuarioPtr &value)
{
    usuario = value;
}


string Entrada::getFornecedor() const
{
    return fornecedor;
}

void Entrada::setFornecedor(const string &value)
{
    fornecedor = value;
}
Entrada::Entrada()
{
}

Entrada::Entrada(sql::ResultSet &rs)
{
    id = rs.getInt(1);
    data = rs.getString(2);
    fornecedor = rs.getString(3);
    anotacao = rs.getString(4);
}

string Entrada::getSqlInsert()
{
    string sql = "INSERT INTO entrada(data, fornecedor, anotacao)\
           VALUES ('"+data+"', '"+fornecedor+"', '"+anotacao+"');";

    return sql;
}

string Entrada::getAnotacao() const
{
    return anotacao;
}

void Entrada::setAnotacao(const string &value)
{
    anotacao = value;
}
