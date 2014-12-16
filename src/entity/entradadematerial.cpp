#include "entradadematerial.h"
#include "util.hpp"

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
    valor = rs.get<double>(4);
    quantidade = rs.get<int>(5);
    entrada = EntradaPtr(new Entrada);
    entrada->setId(rs.get<int>(6));
    entrada->setData(to_string( rs.get<std::tm>(7)) );
    entrada->setFornecedor(rs.get<string>(8));
    entrada->setAnotacao(rs.get<string>(9));
    //entrada->setUsuario(rs.get<int>(10));
    material = MateiralPtr(new Mateiral);
    material->setId(rs.get<int>(11));
    material->setNome(rs.get<string>(12));
    material->setDescricao(rs.get<string>(13));
    material->setImagem(rs.get<string>(14));
    material->setQuantidade(rs.get<int>(15));
	lote = LotePtr(new Lote);
    lote->setId(rs.get<int>(17, 0));
    lote->setNome(rs.get<string>(18, ""));
    lote->setValidade(to_string(rs.get<tm>(19, tm())));
    lote->setQuantidade(rs.get<int>(20, 0));
    material->setGrupo(GrupoPtr(new Grupo(rs.get<string>(22, ""))));
}

string EntradaDeMaterial::getSqlInsert()
{
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote_id, valor, quantidade) \
                                   VALUES('" + to_string(entrada->getId()) + "', '" + to_string(material->getId()) + "', " + (lote->getId()>0?"'"+to_string(lote->getId())+"'":"NULL") + ", '" + to_string(valor) + "', '" + to_string(quantidade) + "')";
    return sql;
}
