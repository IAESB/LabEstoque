#include "pesquisa.h"


int Pesquisa::getId() const
{
    return id;
}

void Pesquisa::setId(int value)
{
    id = value;
}

string Pesquisa::getNome() const
{
    return nome;
}

void Pesquisa::setNome(const string &value)
{
    nome = value;
}

string Pesquisa::getData_inicial() const
{
    return data_inicial;
}

void Pesquisa::setDataInicial(const string &value)
{
    data_inicial = value;
}

string Pesquisa::getData_fianal() const
{
    return data_fianal;
}

void Pesquisa::setDataFianal(const string &value)
{
    data_fianal = value;
}

bool Pesquisa::IsEntrada() const
{
    return isEntrada;
}

void Pesquisa::setIsEntrada(bool value)
{
    isEntrada = value;
}

bool Pesquisa::IsSaida() const
{
    return isSaida;
}

void Pesquisa::setIsSaida(bool value)
{
    isSaida = value;
}

int Pesquisa::getQuantidadeMaterialDe() const
{
    return quantidadeMaterialDe;
}

void Pesquisa::setQuantidadeMaterialDe(int value)
{
    quantidadeMaterialDe = value;
}

int Pesquisa::getQuantidadeMaterialAte() const
{
    return quantidadeMaterialAte;
}

void Pesquisa::setQuantidadeMaterialAte(int value)
{
    quantidadeMaterialAte = value;
}

string Pesquisa::getLote() const
{
	return lote;
}

void Pesquisa::setLote(const string &value)
{
	lote = value;
}

string Pesquisa::getFornecedor() const
{
	return fornecedor;
}

void Pesquisa::setFornecedor(const string &value)
{
	fornecedor = value;
}

string Pesquisa::getValidadade() const
{
    return validadade;
}

void Pesquisa::setValidadade(const string &value)
{
    validadade = value;
}

float Pesquisa::getValor() const
{
    return valor;
}

void Pesquisa::setValor(float value)
{
    valor = value;
}

int Pesquisa::getQuantidadeEntradaDe() const
{
    return quantidadeEntradaDe;
}

void Pesquisa::setQuantidadeEntradaDe(int value)
{
    quantidadeEntradaDe = value;
}

int Pesquisa::getQuantidadeSaidaDe() const
{
    return quantidadeSaidaDe;
}

void Pesquisa::setQuantidadeSaidaDe(int value)
{
    quantidadeSaidaDe = value;
}

int Pesquisa::getQuantidadeEntradaAte() const
{
    return quantidadeEntradaAte;
}

void Pesquisa::setQuantidadeEntradaAte(int value)
{
    quantidadeEntradaAte = value;
}

int Pesquisa::getUsuario_id() const
{
    return usuario_id;
}

void Pesquisa::setUsuario_id(int value)
{
    usuario_id = value;
}

int Pesquisa::getQuantidadeSaidaAte() const
{
	return quantidadeSaidaAte;
}

void Pesquisa::setQuantidadeSaidaAte(int value)
{
	quantidadeSaidaAte = value;
}

string Pesquisa::getSolicitante() const
{
	return solicitante;
}

void Pesquisa::setSolicitante(const string& value)
{
	solicitante = value;
}

vector<string> Pesquisa::getMateriais() const
{
    return materiais;
}

void Pesquisa::setMateriais(const vector<string> &value)
{
    materiais = value;
}

string Pesquisa::getLaboratorio() const
{
    return laboratorio;
}

void Pesquisa::setLaboratorio(const string &value)
{
    laboratorio = value;
}
Pesquisa::Pesquisa()
{
}
