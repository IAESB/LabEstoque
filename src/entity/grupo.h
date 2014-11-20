#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <vector>
#include <memory>
#include <soci/row.h>
using namespace std;

class Grupo
{
    int id;
    string nome;
    shared_ptr<Grupo> grupo;
public:
    Grupo();
    Grupo(const string& nome);
    Grupo(soci::row& r);
    string getSqlInsert();
    int getId() const;
    void setId(int value);
    string getNome() const;
    void setNome(const string &value);
    shared_ptr<Grupo> getGrupo() const;
    void setGrupo(const shared_ptr<Grupo> &value);
};

typedef shared_ptr<Grupo> GrupoPtr;
typedef shared_ptr<vector<GrupoPtr>> GrupoList;

#endif // GRUPO_H
