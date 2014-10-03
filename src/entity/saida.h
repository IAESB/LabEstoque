#ifndef SAIDA_H
#define SAIDA_H

#include "usuario.h"
#include "mateiral.h"
#include "laboratorio.h"
#include "solicitante.h"

class Saida
{
    int id;
    int quantidade;
    string data;
    UsuarioPtr usuario;
    MateiralPtr material;
    LaboratorioPtr laboratorio;
    SolicitantePtr solicitante;
public:
    Saida();
};

#endif // SAIDA_H
