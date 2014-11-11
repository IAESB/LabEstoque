#ifndef RELATORIO_H
#define RELATORIO_H

#include <iostream>
#include <vector>
using namespace std;

class Pesquisa
{
    int id;
    string nome;
    string data_inicial;
    string data_fianal;
    bool isEntrada;
    bool isSaida;
    vector<string> materiais;
    int quantidadeMaterialDe;
    int quantidadeMaterialAte;
	string fornecedor;
    string lote;
    string validadade;
    float valor;
    int quantidadeEntradaDe;
    int quantidadeEntradaAte;
	string solicitante;
	string laboratorio;
    int quantidadeSaidaDe;
    int quantidadeSaidaAte;
    int usuario_id;

public:
    Pesquisa();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    string getData_inicial() const;
    void setDataInicial(const string &value);
    string getData_fianal() const;
    void setDataFianal(const string &value);
    bool IsEntrada() const;
    void setIsEntrada(bool value);
    bool IsSaida() const;
    void setIsSaida(bool value);
    int getQuantidadeMaterialDe() const;
    void setQuantidadeMaterialDe(int value);
    int getQuantidadeMaterialAte() const;
	void setQuantidadeMaterialAte(int value);
	string getLote() const;
	void setLote(const string &value);
	string getFornecedor() const;
	void setFornecedor(const string &value);
    string getValidadade() const;
    void setValidadade(const string &value);
    float getValor() const;
    void setValor(float value);
    int getQuantidadeEntradaDe() const;
    void setQuantidadeEntradaDe(int value);
    int getQuantidadeSaidaDe() const;
    void setQuantidadeSaidaDe(int value);
    int getQuantidadeEntradaAte() const;
    void setQuantidadeEntradaAte(int value);
    int getUsuario_id() const;
    void setUsuario_id(int value);
	string getSolicitante() const;
	void setSolicitante(const string &value);
    int getQuantidadeSaidaAte() const;
    void setQuantidadeSaidaAte(int value);
    vector<string> getMateriais() const;
    void setMateriais(const vector<string> &value);
    string getLaboratorio() const;
    void setLaboratorio(const string &value);
};

#endif // RELATORIO_H
