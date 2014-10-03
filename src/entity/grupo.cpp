#include "grupo.h"


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
Grupo::Grupo()
{
}

string Grupo::getSqlInsert()
{
    string grupoId = "NULL";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "INSERT INTO grupo (nome, grupo_id)\
            VALUES ('"+nome+"', '"+grupoId+"');";

    return sql;
}
