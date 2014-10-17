#include "mateiral.h"

string Mateiral::getDescricao() const
{
    return descricao;
}

void Mateiral::setDescricao(const string &value)
{
    descricao = value;
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

string Mateiral::getImagem() const
{
    return imagem;
}

void Mateiral::setImagem(const string &value)
{
    imagem = value;
}

int Mateiral::getQuantidade() const
{
    return quantidade;
}

void Mateiral::setQuantidade(int value)
{
    quantidade = value;
}
Mateiral::Mateiral()
{
}

Mateiral::Mateiral(const int& id)
{
    this->id = id;
}

Mateiral::Mateiral(sql::ResultSet &rs)
{
    id = rs.getInt64(1);
    nome = rs.getString(2);
    descricao = rs.getString(3);
    imagem = rs.getString(4);
    quantidade = rs.getInt(5);
    GrupoPtr grupo(new Grupo);
    grupo->setId(rs.getInt(6));
    if(rs.findColumn("grupo_nome"))
        grupo->setNome(rs.getString(7));
    setGrupo(grupo);
}

string Mateiral::getSqlInsert()
{
    string grupoId = "";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "INSERT INTO material (nome, descricao, imagem, quantidade";
    sql += grupoId.size()?", grupo_id)":")";
    sql += "VALUES ('"+nome+"', '"+descricao+"', '"+imagem+"', '"+to_string(quantidade)+"'";
    sql += grupoId.size()?", '"+grupoId+"');":");";

    return sql;
}

string Mateiral::getSqlUpdate()
{
    string grupoId = "NULL";
    if(grupo){
        grupoId = to_string(grupo->getId());
    }
    string sql = "UPDATE material \
                 SET nome='"+nome+"', descricao='"+descricao+"', imagem='"+imagem+"', quantidade='"+to_string(quantidade)+"', grupo_id='"+grupoId+"'\
                 WHERE id="+to_string(id)+";";

    return sql;
}

string Mateiral::getSqlDelete()
{
    string sql = "DELETE FROM material WHERE id="+to_string(id);
    return sql;
}
