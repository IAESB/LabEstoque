#ifndef Controlador_H
#define Controlador_H

#include <mongoose/WebController.h>

using namespace std;
using namespace Mongoose;

class Controlador : public WebController
{
public:
    Controlador();
    void mensagem(StreamResponse& response, const string& htmlTextErro);
};

#endif // Controlador_H
