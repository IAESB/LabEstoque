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

}

string EntradaDeMaterial::getSqlInsert()
{
    string sql = "INSERT INTO entrada_de_material(entrada_id, material_id, lote, valor, validade, quantidade) \
                  VALUES('"+to_string(entrada->getId())+"', '"+to_string(material->getId())+"', '"+lote+"', '"+to_string(valor)+"', '"+validade+"', '"+to_string(quantidade)+"')";
    return sql;
}
