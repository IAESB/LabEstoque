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

Entrada::Entrada(soci::row &rs)
{
    id = rs.get<int>(0);
    data = rs.get<string>(1);
    fornecedor = rs.get<string>(2);
    anotacao = rs.get<string>(3);
}

string Entrada::getSqlInsert()
{
    string sql = "INSERT INTO entrada(data, fornecedor, anotacao)\
           VALUES ('"+data+"', '"+fornecedor+"', '"+anotacao+"');";

    return sql;
}

string Entrada::getSqlUpdate()
{
	string sql = "UPDATE entrada SET data='" + data + "', fornecedor='" + fornecedor + "', anotacao='" + anotacao + "' WHERE id="+to_string(id);

	return sql;
}

string Entrada::getSqlDelete()
{
	string sql = "DELETE FROM entrada WHERE id=" + to_string(id) + ";";
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
