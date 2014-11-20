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

LotePtr SaidaDeMaterial::getLote() const
{
    return lote;
}

void SaidaDeMaterial::setLote(const LotePtr &value)
{
    lote = value;
}

SaidaDeMaterial::SaidaDeMaterial()
{
}

SaidaDeMaterial::SaidaDeMaterial(soci::row &rs)
{
    saida = SaidaPtr(new Saida(rs.get<int>(2)));
    material = MateiralPtr(new Mateiral(rs.get<int>(3)));
    lote = LotePtr(new Lote(rs.get<int>(4)));
    quantidade = rs.get<int>(5);
    material->setQuantidade(quantidade);
    lote->setQuantidade(quantidade);
}

string SaidaDeMaterial::getSqlInsert()
{
    string loteId = lote->getId()?"'"+to_string(lote->getId())+"'":"NULL";
    return "INSERT INTO saida_de_material (saida_id, material_id, quantidade, lote_id) \
            VALUE ('" + to_string(saida->getId()) + "', '" + to_string(material->getId()) + "', '" + to_string(quantidade) + "', "+loteId+")";
}

string SaidaDeMaterial::getSqlUpdate()
{
    return "UPDATE saida_de_material SET material_id='" + to_string(material->getId()) + "', quantidade='" + to_string(quantidade) + "', lote='"+to_string(lote->getId())+"' \
			WHERE saida_id='" + to_string(saida->getId()) + "' ;";
}
