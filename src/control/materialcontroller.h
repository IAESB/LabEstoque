#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include "controlador.h"
#include "model/materialmodel.h"

using namespace std;
using namespace Mongoose;

class MaterialController :  public Controlador
{
    MaterialModel model;
public:
    MaterialController();
	void listaMateriais(Request &request, StreamResponse &response);
	void salvarMaterial(Request &request, StreamResponse &response);
	void excluirMaterial(Request &request, StreamResponse &response);
	void alterarMaterial(Request &request, StreamResponse &response);
    void setup();
};

#endif // MATERIALCONTROLLER_H
