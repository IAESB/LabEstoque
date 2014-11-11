#ifndef Controlador_H
#define Controlador_H

#include <mongoose/WebController.h>
#include <mongoose/Server.h>

using namespace std;
using namespace Mongoose;

class Controlador : public WebController
{
public:
    Controlador();
    void mensagem(StreamResponse& response, const string& htmlTextErro);
	void redirecionar(StreamResponse& response, const string& local);
};

#endif // Controlador_H
