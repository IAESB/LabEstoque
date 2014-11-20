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

EntradaDeMaterial::EntradaDeMaterial(soci::row& rs)
{
    valor = rs.get<double>(5);
    quantidade = rs.get<int>(6);
    entrada = EntradaPtr(new Entrada);
    entrada->setId(rs.get<int>(7));
    entrada->setData(rs.get<string>(8));
    entrada->setFornecedor(rs.get<string>(9));
    entrada->setAnotacao(rs.get<string>(10));
    //entrada->setUsuario(rs.get<int>(10));
    material = MateiralPtr(new Mateiral);
    material->setId(rs.get<int>(12));
    material->setNome(rs.get<string>(13));
    material->setDescricao(rs.get<string>(14));
    material->setImagem(rs.get<string>(15));
    material->setQuantidade(rs.get<int>(16));
	lote = LotePtr(new Lote);
    lote->setId(rs.get<int>(18));
    lote->setNome(rs.get<string>(19));
    lote->setValidade(rs.get<string>(20));
    lote->setQuantidade(rs.get<int>(21));
}

string EntradaDeMaterial::getSqlInsert()
{
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote_id, valor, quantidade) \
                                   VALUES('" + to_string(entrada->getId()) + "', '" + to_string(material->getId()) + "', " + (lote->getId()>0?"'"+to_string(lote->getId())+"'":"NULL") + ", '" + to_string(valor) + "', '" + to_string(quantidade) + "')";
    return sql;
}
