#ifndef LABORATORIO_H
#define LABORATORIO_H

#include <iostream>
#include <memory>
using namespace std;

class Laboratorio
{
    int id;
    string nome;
public:
    Laboratorio();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
};
typedef shared_ptr<Laboratorio> LaboratorioPtr;
#endif // LABORATORIO_H
