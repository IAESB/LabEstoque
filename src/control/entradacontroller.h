#ifndef ENTRADACONTROLLER_H
#define ENTRADACONTROLLER_H

#include "controlador.h"
#include "model/entradamodel.h"

class EntradaController : public Controlador
{
    EntradaModel model;
public:
    EntradaController();
	void listaEntrada(Request &request, StreamResponse &response);
	void salvaEntrada(Request &request, StreamResponse &response);
	void alterarEntrada(Request &request, StreamResponse &response);
    void getEntrada(Request &request, StreamResponse &response);
    void setup();
private:
	EntradaDeMaterialList criarEntradas(Request& request);
};

#endif // ENTRADACONTROLLER_H
