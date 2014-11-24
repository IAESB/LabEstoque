#include "saida.h"
#include "util.hpp"


int Saida::getId() const
{
    return id;
}

void Saida::setId(int value)
{
    id = value;
}


string Saida::getData() const
{
    return data;
}

void Saida::setData(const string &value)
{
    data = value;
}

UsuarioPtr Saida::getUsuario() const
{
    return usuario;
}

void Saida::setUsuario(const UsuarioPtr &value)
{
    usuario = value;
}

LaboratorioPtr Saida::getLaboratorio() const
{
    return laboratorio;
}

void Saida::setLaboratorio(const LaboratorioPtr &value)
{
    laboratorio = value;
}

SolicitantePtr Saida::getSolicitante() const
{
    return solicitante;
}

void Saida::setSolicitante(const SolicitantePtr &value)
{
    solicitante = value;
}

SaidaDeMaterialList Saida::getSaidaDeMaterialList() const
{
    return materiais;
}

void Saida::setSaidaDeMateriais(const SaidaDeMaterialList &value)
{
    materiais = value;
}
Saida::Saida()
{
}

Saida::Saida(int id)
{
    this->id = id;
}

Saida::Saida(soci::row &rs)
{
    id = rs.get<int>(0);
    data = to_string( rs.get<tm>(1));
    laboratorio = LaboratorioPtr(new Laboratorio(rs.get<int>(2)));
    solicitante = SolicitantePtr(new Solicitante(rs.get<int>(3)));
    //usuario = rs.get(4)
    if(rs.size()>6){
        laboratorio->setNome(rs.get<string>("lab"));
        solicitante->setNome(rs.get<string>("solicitante"));
    }
}

string Saida::getSqlInsert()
{
    string sql = "INSERT INTO saida(data, laboratorio_id";
    sql += solicitante?", solicitante_id)":")";
    sql+= "VALUE( '"+data+"', '"+to_string(laboratorio->getId())+"'";
    sql += solicitante?", '"+to_string(solicitante->getId())+"')":")";
    return sql;
}


string Saida::getSqlUpdate()
{
	string sql = "UPDATE saida SET data='" + data + "', laboratorio_id='" + to_string(laboratorio->getId()) + "'";
	sql += solicitante ? ", solicitante_id='" + to_string(solicitante->getId()) + "'" : "";
	sql += " WHERE id="+to_string(id);
	return sql;
}

string Saida::getSqlDelete()
{
	return "DELETE FROM saida WHERE id=" + to_string(id);
}
