#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <memory>
using namespace std;

class Grupo
{
    int id;
    string nome;
    shared_ptr<Grupo> grupo;
public:
    Grupo();
    string getSqlInsert();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    shared_ptr<Grupo> getGrupo() const;
    void setGrupo(const shared_ptr<Grupo> &value);
};

typedef shared_ptr<Grupo> GrupoPtr;

#endif // GRUPO_H
