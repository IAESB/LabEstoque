#ifndef RELATORIOCONTROLLER_H
#define RELATORIOCONTROLLER_H

#include "controlador.h"
#include "model/pesquisamodel.h"

class PesquisaController : public Controlador
{
    PesquisaModel model;
public:
    PesquisaController();
    void setup();
    void listaRelatorio(Request& request, StreamResponse& response);
    void pesquisarRelatorio(Request& request, StreamResponse& response);

private:
    Pesquisa criarPesquisa(Request& response);
};

#endif // RELATORIOCONTROLLER_H
