#include "mateiral.h"


string Mateiral::getValidade() const
{
    return validade;
}

void Mateiral::setValidade(const string &value)
{
    validade = value;
}

string Mateiral::getLote() const
{
    return lote;
}

void Mateiral::setLote(const string &value)
{
    lote = value;
}

string Mateiral::getFormula() const
{
    return formula;
}

void Mateiral::setFormula(const string &value)
{
    formula = value;
}

string Mateiral::getNome() const
{
    return nome;
}

void Mateiral::setNome(const string &value)
{
    nome = value;
}

int Mateiral::getId() const
{
    return id;
}

void Mateiral::setId(int value)
{
    id = value;
}

GrupoPtr Mateiral::getGrupo() const
{
    return grupo;
}

void Mateiral::setGrupo(const GrupoPtr &value)
{
    grupo = value;
}
Mateiral::Mateiral()
{
}

Mateiral::Mateiral(sql::ResultSet &rs)
{
    id = rs.getInt64(1);
    nome = rs.getString(2);
    formula = rs.getString(3);
    lote = rs.getString(4);
    validade = rs.getString(5);
    GrupoPtr grupo(new Grupo);
    grupo->setId(rs.getInt(6));
    grupo->setNome(rs.getString(7));
    setGrupo(grupo);
}

string Mateiral::getSqlInsert()
{
    string grupoId = "NULL";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "INSERT INTO material (nome, formula, lote, validade, grupo_id)\
            VALUES ('"+nome+"', '"+formula+"', '"+lote+"', '"+validade+"', '"+grupoId+"');";

    return sql;
}

string Mateiral::getSqlUpdate()
{
    string grupoId = "NULL";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "UPDATE material \
                 SET(nome='"+nome+"', formula'"+formula+"', lote'"+lote+"', validade'"+validade+"', grupo_id'"+grupoId+"')\
                 WHERE id="+to_string(id)+";";

    return sql;
}

string Mateiral::getSqlDelete()
{
    string sql = "DELETE FROM material WHERE id="+to_string(id);
    return sql;
}
