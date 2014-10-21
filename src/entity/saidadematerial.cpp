#include "saidadematerial.h"


SaidaPtr SaidaDeMaterial::getSaida() const
{
    return saida;
}

void SaidaDeMaterial::setSaida(const SaidaPtr &value)
{
    saida = value;
}

MateiralPtr SaidaDeMaterial::getMaterial() const
{
    return material;
}

void SaidaDeMaterial::setMaterial(const MateiralPtr &value)
{
    material = value;
}

int SaidaDeMaterial::getQuantidade() const
{
    return quantidade;
}

void SaidaDeMaterial::setQuantidade(int value)
{
    quantidade = value;
}
SaidaDeMaterial::SaidaDeMaterial()
{
}

SaidaDeMaterial::SaidaDeMaterial(sql::ResultSet &rs)
{
    saida = SaidaPtr(new Saida(rs.getInt(1)));
    material = MateiralPtr(new Mateiral(rs.getInt(2)));
    quantidade = rs.getInt(3);
}

string SaidaDeMaterial::getSqlInsert()
{
	return "INSERT INTO saida_de_material (saida_id, material_id, quantidade) \
		               VALUE ('" + to_string(saida->getId()) + "', '" + to_string(material->getId()) + "', '" + to_string(quantidade) + "')";
}

string SaidaDeMaterial::getSqlUpdate()
{
	return "UPDATE saida_de_material SET material_id='" + to_string(material->getId()) + "', quantidade='" + to_string(quantidade) + "' \
			WHERE saida_id='" + to_string(saida->getId()) + "' ;";
}
