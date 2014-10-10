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
    void setup();
};

#endif // ENTRADACONTROLLER_H
