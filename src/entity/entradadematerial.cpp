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
    valor = rs.getDouble(3);
    quantidade = rs.getInt(4);
    entrada = EntradaPtr(new Entrada);
    entrada->setId(rs.getInt(6));
    entrada->setData(rs.getString(7));
    entrada->setFornecedor(rs.getString(8));
    entrada->setAnotacao(rs.getString(9));
    //entrada->setUsuario(rs.getint(10));
    material = MateiralPtr(new Mateiral);
    material->setId(rs.getInt(11));
    material->setNome(rs.getString(12));
    material->setDescricao(rs.getString(13));
	material->setImagem(rs.getString(14));
	material->setQuantidade(rs.getInt(15));
	lote = LotePtr(new Lote);
	lote->setId(rs.getInt(17));
	lote->setNome(rs.getString(18));
	lote->setValidade(rs.getString(19));
	lote->setQuantidade(rs.getInt(20));
}

string EntradaDeMaterial::getSqlInsert()
{
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote_id, valor, quantidade) \
                                   VALUES('" + to_string(entrada->getId()) + "', '" + to_string(material->getId()) + "', " + (lote->getId()>0?"'"+to_string(lote->getId())+"'":"NULL") + ", '" + to_string(valor) + "', '" + to_string(quantidade) + "')";
    return sql;
}
