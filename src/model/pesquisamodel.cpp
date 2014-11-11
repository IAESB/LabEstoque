#include "pesquisamodel.h"

PesquisaModel::PesquisaModel()
{
}

MateiralList PesquisaModel::getListMaterial()
{
    return materialModel.getListMaterial();
}

EntradaDeMaterialList PesquisaModel::getListEntradaDeMaterial(Pesquisa &pesquisa)
{
    return entradaDeMaterialModel.getListEntradaDeMaterial(pesquisa);
}

SaidaDeMaterialList PesquisaModel::getListSaidaDeMaterial(Pesquisa &pesquisa)
{
    return saidaDeMaterialModel.getListSaidaDeMaterial(pesquisa);
}
