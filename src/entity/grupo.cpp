#include "grupo.h"


Grupo::Grupo()
{
}

Grupo::Grupo(const string& nome)
{
    this->nome = nome;
}

Grupo::Grupo(soci::row& rs)
{
    id = rs.get<int>(0);
    nome = rs.get<string>(1);
}

int Grupo::getId() const
{
    return id;
}

void Grupo::setId(int value)
{
    id = value;
}

string Grupo::getNome() const
{
    return nome;
}

void Grupo::setNome(const string &value)
{
    nome = value;
}

shared_ptr<Grupo> Grupo::getGrupo() const
{
    return grupo;
}

void Grupo::setGrupo(const shared_ptr<Grupo> &value)
{
    grupo = value;
}

string Grupo::getSqlInsert()
{
    string grupoId = "";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "INSERT INTO grupo (nome";
    sql += grupoId.size()?", grupo_id)":")";
    sql += "VALUES ('"+nome+"'";
    sql += grupoId.size()?", '"+grupoId+"');":");";

    return sql;
}
