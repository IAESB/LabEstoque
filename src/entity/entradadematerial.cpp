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

float EntradaDeMaterial::getValor() const
{
    return valor;
}

void EntradaDeMaterial::setValor(float value)
{
    valor = value;
}

int EntradaDeMaterial::getQuantidade() const
{
    return quantidade;
}

void EntradaDeMaterial::setQuantidade(int value)
{
    quantidade = value;
}

LotePtr EntradaDeMaterial::getLote() const
{
    return lote;
}

void EntradaDeMaterial::setLote(const LotePtr &value)
{
    lote = value;
}
EntradaDeMaterial::EntradaDeMaterial()
{
}

EntradaDeMaterial::EntradaDeMaterial(sql::ResultSet &rs)
{
    valor = rs.getDouble(5);
    quantidade = rs.getInt(6);
    entrada = EntradaPtr(new Entrada);
    entrada->setId(rs.getInt(7));
    entrada->setData(rs.getString(8));
    entrada->setFornecedor(rs.getString(9));
    entrada->setAnotacao(rs.getString(10));
    //entrada->setUsuario(rs.getint(10));
    material = MateiralPtr(new Mateiral);
    material->setId(rs.getInt(12));
    material->setNome(rs.getString(13));
    material->setDescricao(rs.getString(14));
    material->setImagem(rs.getString(15));
    material->setQuantidade(rs.getInt(16));
	lote = LotePtr(new Lote);
    lote->setId(rs.getInt(18));
    lote->setNome(rs.getString(19));
    lote->setValidade(rs.getString(20));
    lote->setQuantidade(rs.getInt(21));
}

string EntradaDeMaterial::getSqlInsert()
{
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote_id, valor, quantidade) \
                                   VALUES('" + to_string(entrada->getId()) + "', '" + to_string(material->getId()) + "', " + (lote->getId()>0?"'"+to_string(lote->getId())+"'":"NULL") + ", '" + to_string(valor) + "', '" + to_string(quantidade) + "')";
    return sql;
}
