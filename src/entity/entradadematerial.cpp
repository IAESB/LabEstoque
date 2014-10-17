#include "entradadematerial.h"


EntradaPtr EntradaDeMaterial::getEntrada() const
{
    return entrada;
}

void EntradaDeMaterial::setEntrada(const EntradaPtr &value)
{
    entrada = value;
}

MateiralPtr EntradaDeMaterial::getMaterial() const
{
    return material;
}

void EntradaDeMaterial::setMaterial(const MateiralPtr &value)
{
    material = value;
}

string EntradaDeMaterial::getLote() const
{
    return lote;
}

void EntradaDeMaterial::setLote(const string &value)
{
    lote = value;
}

float EntradaDeMaterial::getValor() const
{
    return valor;
}

void EntradaDeMaterial::setValor(float value)
{
    valor = value;
}

string EntradaDeMaterial::getValidade() const
{
    return validade;
}

void EntradaDeMaterial::setValidade(const string &value)
{
    validade = value;
}

int EntradaDeMaterial::getQuantidade() const
{
    return quantidade;
}

void EntradaDeMaterial::setQuantidade(int value)
{
    quantidade = value;
}
EntradaDeMaterial::EntradaDeMaterial()
{
}

EntradaDeMaterial::EntradaDeMaterial(sql::ResultSet &rs)
{
    lote = rs.getString(3);
    valor = rs.getDouble(4);
    validade = rs.getString(5);
    quantidade = rs.getInt(6);
    entrada = EntradaPtr(new Entrada);
    entrada->setId(rs.getInt(7));
    entrada->setData(rs.getString(8));
    entrada->setFornecedor(rs.getString(9));
    entrada->setAnotacao(rs.getString(10));
    //entrada->setUsuario(rs.getint(11));
    material = MateiralPtr(new Mateiral);
    material->setId(rs.getInt(12));
    material->setNome(rs.getString(13));
    material->setDescricao(rs.getString(14));
    //material->setGrupo(rs.getInt(15));
    material->setImagem(rs.getString(16));
}

string EntradaDeMaterial::getSqlInsert()
{
	string validade = this->validade.empty() ? "NULL" : "'" + this->validade + "'";
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote, valor, validade, quantidade) \
                  VALUES('"+to_string(entrada->getId())+"', '"+to_string(material->getId())+"', '"+lote+"', '"+to_string(valor)+"', "+validade+", '"+to_string(quantidade)+"')";
    return sql;
}
