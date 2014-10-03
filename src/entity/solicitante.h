#ifndef SOLICITANTE_H
#define SOLICITANTE_H

#include <iostream>
#include <memory>
using namespace std;

class Solicitante
{
    int id;
    string nome;
    string matricula;
public:
    Solicitante();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    string getMatricula() const;
    void setMatricula(const string &value);
};
typedef shared_ptr<Solicitante> SolicitantePtr;

#endif // SOLICITANTE_H
